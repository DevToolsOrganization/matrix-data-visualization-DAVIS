# FileRecognizer rules

## 📋 Список представлений данных в файле

### 1-Line Charts X AUTO Y FIRST
| ID | TYPE | X | Y | MODE |
|----|------|-------|-----|------|
| 0010 | H → 1 LINE | AUTO | FIRST | DEFAULT |
| 0021 | H ← 1 LINE | AUTO | FIRST | OPTION |
| 0030 | V ↓ 1 LINE | AUTO | FIRST | DEFAULT |
| 0041 | V ↑ 1 LINE | AUTO | FIRST | OPTION |

### 2-Lines Charts
| ID | TYPE | X | Y | MODE |
|----|------|-------|-----|------|
| 0050 | H → 2 LINES | FIRST | SECOND | DEFAULT |
| 0061 | H ← 2 LINES | FIRST | SECOND | OPTION |
| 0071 | H → 2 LINES | SECOND | FIRST | OPTION |
| 0081 | H ← 2 LINES | SECOND | FIRST | OPTION |
| 0090 | V ↓ 2 LINES | FIRST | SECOND | DEFAULT |
| 0101 | V ↓ 2 LINES | SECOND | FIRST | OPTION |
| 0111 | V ↑ 2 LINES | SECOND | FIRST | OPTION |
| 0121 | V ↑ 2 LINES | FIRST | SECOND | OPTION |

### 2-Lines Charts TIMELINE
| ID | TYPE | X | Y | MODE |
|----|------|-------|-----|------|
| 0130 | H → 2 LINES | TIME | VALUES | DEFAULT |
| 0141 | H ← 2 LINES | TIME | VALUES | OPTION |
| 0151 | H → 2 LINES | VALUES | TIME | OPTION |
| 0161 | H ← 2 LINES | VALUES | TIME | OPTION |
| 0170 | V ↓ 2 LINES | TIME | VALUES | DEFAULT |
| 0181 | V ↓ 2 LINES | VALUES | TIME | OPTION |
| 0191 | V ↑ 2 LINES | TIME | VALUES | OPTION |
| 0201 | V ↑ 2 LINES | VALUES | TIME | OPTION |

### Heatmaps
| ID | TYPE | X | Y | MODE |
|----|------|---|-----|------|
| 0210 | M → HEAT_MAP | - | - | DEFAULT |
| 0221 | M ↑ HEAT_MAP | - | - | OPTION |
| 0231 | M ↓ HEAT_MAP | - | - | OPTION |
| 0241 | M → HEAT_MAP | - | - | OPTION |

## 📖 Легенда кодирования ID (ABCD)

**Формат**: `ABCD` где:
- ABC* = порядковый номер представления
- ***D = MODE (0=DEFAULT, 1=OPTION)

### Направление чтения данных
H → = 0 (Horizontal Right)
H ← = 1 (Horizontal Left)
V ↓ = 2 (Vertical Down)
V ↑ = 3 (Vertical Up)
