# ❓ FAQ

### Generated html page is empty in browser
Check you building folder, find folder **davis_htmls** and check if **plotly-2.32.0.min.js** exists.
If it not exists copy this file manualy to this place.<br>
And create bug issue :)

### Can I use  newer Plotly .js file?
All our test are made for plotly .js file which is placed at our last [release](https://github.com/valvals/devtools/releases) <br>
But probably newer version will also work. So download newer .js file [at plotly page](https://plotly.com/javascript/), rename it to **plotly-2.32.0.min.js** and test by yorself.

### Which containers can I use in show() function?
Containers must support implementation of `begin()` and `end()` methods. Content of containers must be convertable to `double`

[Next page →](/LICENSE.md)