# Loan ALLARD
# Romain CANTOR
# Willem CHETIOUI


---
 
## 2.4 Mesurer un algorithme simple
 
### Code source analysé
 
Implémentation simplifiée du QuickSort :
 
```c
 1  void iqsort0(int *a, int n)
 2  {
 3      int i, j;
 4      if (n <= 1)
 5          return;
 6      for (i = 1, j = 0; i < n; i++)
 7          if (a[i] < a[0])
 8              swap(++j, i, a);
 9      swap(0, j, a);
10      iqsort0(a, j);
11      iqsort0(a + j + 1, n - j - 1);
12  }
```
 
---
 
### Graphe de flot de contrôle (CFG)
 
```mermaid
flowchart TD
  S([Entrée]) --> B1{"B1 : if n #lt;= 1<br/>ligne 4"}
  B1 -- vrai --> B2["B2 : return<br/>ligne 5"]
  B1 -- faux --> B3["B3 : i = 1, j = 0<br/>ligne 6"]
  B3 --> B4{"B4 : i #lt; n<br/>ligne 6"}
  B4 -- vrai --> B5{"B5 : a[i] #lt; a[0]<br/>ligne 7"}
  B4 -- faux --> B8["B8 : lignes 9 à 11<br/>swap(0, j, a)<br/>iqsort0(a, j)<br/>iqsort0(a+j+1, n-j-1)"]
  B5 -- vrai --> B6["B6 : swap(++j, i, a)<br/>ligne 8"]
  B5 -- faux --> B7
  B6 --> B7["B7 : i++<br/>ligne 6"]
  B7 --> B4
  B2 --> E([Sortie])
  B8 --> E
```



## 2.5 Complexité cyclomatique

---

### Nombre de nœuds **N** (B1 à B8 + Sortie) = 9 
### Nombre d'arêtes **E** = 11
### Composantes connexes **P** = 1

---
 
### $$V(G) = E - N + 2P = 11 - 9 + 2 = \mathbf{4}$$
 
### **Vérification par les prédicats** : le code contient 3 points de décision (`if (n <= 1)`, `i < n`, `if (a[i] < a[0])`), donc V(G) = 3 + 1 = **4**.
 
### Le nœud d'entrée n'est pas compté ici. L'ajouter donnerait N = 10 et E = 12, et le résultat resterait identique.
 
### **Interprétation** : il existe 4 chemins linéairement indépendants dans `iqsort0`. Il faut donc au minimum 4 cas de test pour couvrir la base de chemins. Une valeur de 4 correspond à une fonction simple, peu risquée et facile à tester.
 

## 2.6 Métriques de Halstead

---

### Convention de comptage (CM, slides 43-44)

- **Opérateurs** : éléments de contrôle (`if`, `for`, `return`), déclarations (fonction, type `int`, pointeur `*`), opérateurs d'affectation, arithmétiques, relationnels et d'indexation.
- **Opérandes** : variables, constantes et **appels de procédures** (`swap`, `iqsort0`), y compris les occurrences dans les déclarations.
- **Ponctuation non comptée** : `( ) { } ; ,` sont des délimiteurs syntaxiques qui n'agissent sur aucune variable.
- `++j` et `i++` sont comptés comme un même opérateur distinct `++`.

---

### Opérateurs

| Opérateur | Occurrences | Lignes |
|---|:-:|---|
| `void iqsort0(…)` (déclaration de fonction) | 1 | 1 |
| `int` (déclaration de type) | 3 | 1 (×2), 3 |
| `*` (déclaration de pointeur) | 1 | 1 |
| `if` | 2 | 4, 7 |
| `return` | 1 | 5 |
| `for` | 1 | 6 |
| `=` | 2 | 6 (×2) |
| `<=` | 1 | 4 |
| `<` | 2 | 6, 7 |
| `++` | 2 | 6, 8 |
| `[ ]` (indexation) | 2 | 7 (×2) |
| `+` | 2 | 11 (×2) |
| `-` | 2 | 11 (×2) |
| **Total** | **22** | |

### Opérandes

| Opérande | Occurrences | Lignes |
|---|:-:|---|
| `a` | 7 | 1, 7 (×2), 8, 9, 10, 11 |
| `n` | 4 | 1, 4, 6, 11 |
| `i` | 6 | 3, 6 (×3), 7, 8 |
| `j` | 7 | 3, 6, 8, 9, 10, 11 (×2) |
| `0` | 3 | 6, 7, 9 |
| `1` | 4 | 4, 6, 11 (×2) |
| `swap` (appel) | 2 | 8, 9 |
| `iqsort0` (appel) | 2 | 10, 11 |
| **Total** | **35** | |

---

### Résultats

| Mesure | Formule | Valeur |
|---|---|:-:|
| Opérateurs distincts | $n_t$ | 13 |
| Occurrences d'opérateurs | $N_t$ | 22 |
| Opérandes distincts | $n_d$ | 8 |
| Occurrences d'opérandes | $N_d$ | 35 |
| Longueur | $N = N_t + N_d$ | **57** |
| Vocabulaire | $n = n_t + n_d$ | **21** |
| Volume | $V = N \times \log_2 n = 57 \times \log_2 21$ | **250,36** |
| Difficulté | $D = \frac{n_t}{2} \times \frac{N_d}{n_d} = 6{,}5 \times 4{,}375$ | **28,44** |
| Effort | $E = D \times V$ | **7 119,67** |

### **Interprétation** : le volume (≈ 250) reste modeste, ce qui est cohérent avec une fonction courte. La difficulté est en revanche assez élevée pour sa taille : peu d'opérandes distincts sont réutilisés très souvent (`a` et `j` apparaissent 7 fois chacun), ce qui demande de suivre leur valeur tout au long de l'algorithme.

### Ces valeurs dépendent directement de la convention choisie : compter la ponctuation ou les types, ou considérer les appels comme des opérateurs, change tous les résultats.
