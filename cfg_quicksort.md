graph TD
    N1["N1: if (n <= 1)"] -->|Vrai| N2["N2: return"]
    N1 -->|Faux| N3["N3: i = 1, j = 0"]
    N3 --> N4["N4: i < n"]
    N4 -->|Vrai| N5["N5: if (a[i] < a[0])"]
    N4 -->|Faux| N8["N8: swap(0,j,a); iqsort0(...); iqsort0(...)"]
    N5 -->|Vrai| N6["N6: swap(++j, i, a)"]
    N5 -->|Faux| N7["N7: i++"]
    N6 --> N7
    N7 --> N4
    N2 --> N9(["N9: FIN"])
    N8 --> N9