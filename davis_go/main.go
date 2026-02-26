package main

import (
    "fmt"
    "io"
    "log"
    "net/http"
    "os"
    "path/filepath"
    "strings"
    "time"
)

func main() {
    http.HandleFunc("/", homeHandler)
    http.HandleFunc("/upload", uploadHandler)
    http.HandleFunc("/files", filesHandler)
    http.HandleFunc("/download/", downloadHandler)
    http.HandleFunc("/health", healthHandler)
    http.HandleFunc("/ping", pingHandler)

    log.Println("Davis HTTP Server: http://localhost:8080")
    log.Fatal(http.ListenAndServe(":8080", nil))
}

func homeHandler(w http.ResponseWriter, r *http.Request) {
    w.Header().Set("Content-Type", "text/html; charset=utf-8")
    
    currentTime := time.Now().Format("2006-01-02 15:04:05")
    html := "<!DOCTYPE html>" +
        "<html><head><meta charset='UTF-8'>" +
        "<title>Davis HTTP Server</title>" +
        "<style>" +
        "body { font-family: Arial; max-width: 900px; margin: 50px auto; padding: 20px; " +
        "background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); color: white; min-height: 100vh; }" +
        ".container { background: rgba(255,255,255,0.1); padding: 40px; border-radius: 20px; }" +
        "h1 { text-align: center; margin-bottom: 10px; }" +
        ".dropzone { border: 4px dashed rgba(255,255,255,0.5); padding: 60px 20px; text-align: center; " +
        "margin: 30px 0; background: rgba(255,255,255,0.1); border-radius: 15px; transition: all 0.3s; cursor: pointer; }" +
        ".dropzone:hover { border-color: rgba(255,255,255,0.8); }" +
        ".dropzone.dragover { border-color: #4ade80; background: rgba(74,222,128,0.2); transform: scale(1.02); }" +
        ".file-list { margin-top: 30px; max-height: 400px; overflow-y: auto; }" +
        ".file-item { padding: 15px; border-radius: 10px; background: rgba(255,255,255,0.15); " +
        "margin-bottom: 10px; display: flex; justify-content: space-between; align-items: center; }" +
        ".progress-bar { width: 100%; height: 8px; background: rgba(255,255,255,0.2); border-radius: 4px; " +
        "overflow: hidden; margin: 10px 0; }" +
        ".progress { height: 100%; background: linear-gradient(90deg, #4ade80, #22c55e); width: 0%; " +
        "transition: width 0.3s; border-radius: 4px; }" +
        ".status { font-weight: bold; color: #4ade80; }" +
        ".endpoints { text-align: center; margin: 30px 0; }" +
        ".endpoint { display: inline-block; margin: 0 15px; padding: 10px 20px; " +
        "background: rgba(255,255,255,0.2); border-radius: 25px; text-decoration: none; color: white; " +
        "transition: all 0.3s; }" +
        ".endpoint:hover { background: rgba(255,255,255,0.3); transform: translateY(-2px); }" +
        ".time { text-align: center; opacity: 0.9; }" +
        "</style></head><body>" +
        "<div class='container'>" +
        "<h1>Davis HTTP Server</h1>" +
        "<p class='time'>Time: " + currentTime + "</p>" +
        "<div class='dropzone' id='dropZone'>" +
        "<h3>Перетащите файлы сюда или кликните</h3>" +
        "<p>Поддерживается множественная загрузка</p>" +
        "<input type='file' id='fileInput' multiple style='display:none;'>" +
        "</div>" +
        "<div id='fileList' class='file-list'></div>" +
        "<div class='endpoints'>" +
        "<a href='/health' class='endpoint'>Health Check</a>" +
        "<a href='/ping' class='endpoint'>API Ping</a>" +
        "<a href='/files' class='endpoint'>Загруженные файлы</a>" +
        "</div></div>" +
        "<script>" +
        "const dropZone=document.getElementById('dropZone');" +
        "const fileInput=document.getElementById('fileInput');" +
        "const fileList=document.getElementById('fileList');" +
        "['dragenter','dragover','dragleave','drop'].forEach(e=>dropZone.addEventListener(e,preventDefaults,false));" +
        "function preventDefaults(e){e.preventDefault();e.stopPropagation();}" +
        "['dragenter','dragover'].forEach(e=>dropZone.addEventListener(e,()=>dropZone.classList.add('dragover'),false));" +
        "['dragleave','drop'].forEach(e=>dropZone.addEventListener(e,()=>dropZone.classList.remove('dragover'),false));" +
        "dropZone.addEventListener('drop',handleDrop,false);" +
        "fileInput.addEventListener('change',handleFiles);" +
        "function handleDrop(e){const files=e.dataTransfer.files;handleFiles(files);}" +
        "function handleFiles(files){Array.from(files).forEach(uploadFile);}" +
        "function uploadFile(file){const formData=new FormData();formData.append('file',file);" +
        "const xhr=new XMLHttpRequest();xhr.open('POST','/upload');" +
        "xhr.upload.addEventListener('progress',e=>{if(e.lengthComputable){const p=(e.loaded/e.total)*100;updateFileStatus(file.name,p);}});"+
        "xhr.addEventListener('load',()=>{if(xhr.status===200){updateFileStatus(file.name,100,'Загружено!');}else{updateFileStatus(file.name,0,'Ошибка');}});"+
        "xhr.addEventListener('error',()=>{updateFileStatus(file.name,0,'Сетевая ошибка');});"+
        "xhr.send(formData);}" +
        "function updateFileStatus(n,p,s=''){let i=document.getElementById('file-'+n);if(!i){i=createFileItem(n);}"+
        "i.querySelector('.progress').style.width=p+'%';i.querySelector('.status').textContent=s||Math.round(p)+'%';}" +
        "function createFileItem(n){const d=document.createElement('div');d.id='file-'+n;d.className='file-item';"+
        "d.innerHTML='<div class=\"file-info\"><strong>'+n+'</strong><div class=\"progress-bar\"><div class=\"progress\"></div></div><span class=\"status\">0%</span></div>';"+
        "fileList.appendChild(d);return d;}" +
        "dropZone.addEventListener('click',()=>fileInput.click());" +
        "</script></body></html>"
    
    fmt.Fprint(w, html)
}

func uploadHandler(w http.ResponseWriter, r *http.Request) {
    if r.Method != http.MethodPost {
        http.Error(w, "Только POST", http.StatusMethodNotAllowed)
        return
    }
    
    os.MkdirAll("./uploads", 0755)
    
    file, header, err := r.FormFile("file")
    if err != nil {
        http.Error(w, "Нет файла", http.StatusBadRequest)
        return
    }
    defer file.Close()
    
    safeName := filepath.Base(header.Filename)
    dstPath := filepath.Join("./uploads", safeName)
    
    dst, err := os.Create(dstPath)
    if err != nil {
        http.Error(w, "Ошибка сохранения", http.StatusInternalServerError)
        return
    }
    defer dst.Close()
    
    io.Copy(dst, file)
    
    w.Header().Set("Content-Type", "application/json; charset=utf-8")
    fmt.Fprintf(w, `{"status":"ok","filename":"%s","size":%d}`, safeName, header.Size)
}

func filesHandler(w http.ResponseWriter, r *http.Request) {
    files, _ := os.ReadDir("./uploads")
    w.Header().Set("Content-Type", "text/html; charset=utf-8")
    
    html := "<h2>Загруженные файлы:</h2><ul>"
    for _, file := range files {
        if !file.IsDir() {
            info, _ := file.Info()
            html += fmt.Sprintf("<li><a href='/download/%s'>%s</a> (%d байт)</li>", 
                file.Name(), file.Name(), info.Size())
        }
    }
    html += "</ul><a href='/'>Назад</a>"
    fmt.Fprint(w, html)
}

func downloadHandler(w http.ResponseWriter, r *http.Request) {
    filename := strings.TrimPrefix(r.URL.Path, "/download/")
    filePath := filepath.Join("./uploads", filename)
    http.ServeFile(w, r, filePath)
}

func healthHandler(w http.ResponseWriter, r *http.Request) {
    w.Header().Set("Content-Type", "application/json; charset=utf-8")
    fmt.Fprintf(w, `{"status":"healthy","timestamp":"%s"}`, time.Now().Format(time.RFC3339))
}

func pingHandler(w http.ResponseWriter, r *http.Request) {
    w.Header().Set("Content-Type", "application/json; charset=utf-8")
    fmt.Fprintf(w, `{"message":"pong","from":"davis_hhtp_server"}`)
}
