# Equipe

- ALLARD Loan
- CANTOR Romain
- CHETIOUI Willem

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

### Convention de comptage

- Les opérateurs sont les mots-clés de contrôle (`if`, `for`, `return`), les déclarations (la fonction, `int`, `*`) et les opérateurs du C (`=`, `<=`, `<`, `++`, `+`, `-`, `[ ]`).
- Les opérandes sont les variables, les constantes et les appels de fonction (`swap`, `iqsort0`), comme dans le cours.
- La ponctuation `( ) { } ; ,` n'est pas comptée.
- `++j` et `i++` comptent comme le même opérateur.

---

### Opérateurs

| Opérateur                                   | Occurrences | Lignes    |
| ------------------------------------------- | :---------: | --------- |
| `void iqsort0(…)` (déclaration de fonction) |      1      | 1         |
| `int` (déclaration de type)                 |      3      | 1 (×2), 3 |
| `*` (déclaration de pointeur)               |      1      | 1         |
| `if`                                        |      2      | 4, 7      |
| `return`                                    |      1      | 5         |
| `for`                                       |      1      | 6         |
| `=`                                         |      2      | 6 (×2)    |
| `<=`                                        |      1      | 4         |
| `<`                                         |      2      | 6, 7      |
| `++`                                        |      2      | 6, 8      |
| `[ ]` (indexation)                          |      2      | 7 (×2)    |
| `+`                                         |      2      | 11 (×2)   |
| `-`                                         |      2      | 11 (×2)   |
| **Total**                                   |   **22**    |           |

### Opérandes

| Opérande          | Occurrences | Lignes                  |
| ----------------- | :---------: | ----------------------- |
| `a`               |      7      | 1, 7 (×2), 8, 9, 10, 11 |
| `n`               |      4      | 1, 4, 6, 11             |
| `i`               |      6      | 3, 6 (×3), 7, 8         |
| `j`               |      7      | 3, 6, 8, 9, 10, 11 (×2) |
| `0`               |      3      | 6, 7, 9                 |
| `1`               |      4      | 4, 6, 11 (×2)           |
| `swap` (appel)    |      2      | 8, 9                    |
| `iqsort0` (appel) |      2      | 10, 11                  |
| **Total**         |   **35**    |                         |

---

### Résultats

| Mesure                   | Formule                                                           |    Valeur    |
| ------------------------ | ----------------------------------------------------------------- | :----------: |
| Opérateurs distincts     | $n_t$                                                             |      13      |
| Occurrences d'opérateurs | $N_t$                                                             |      22      |
| Opérandes distincts      | $n_d$                                                             |      8       |
| Occurrences d'opérandes  | $N_d$                                                             |      35      |
| Longueur                 | $N = N_t + N_d$                                                   |    **57**    |
| Vocabulaire              | $n = n_t + n_d$                                                   |    **21**    |
| Volume                   | $V = N \times \log_2 n = 57 \times \log_2 21$                     |  **250,36**  |
| Difficulté               | $D = \frac{n_t}{2} \times \frac{N_d}{n_d} = 6{,}5 \times 4{,}375$ |  **28,44**   |
| Effort                   | $E = D \times V$                                                  | **7 119,67** |

### Le volume reste modeste, c'est normal pour une fonction aussi courte. La difficulté est plus élevée parce que peu d'opérandes sont réutilisés très souvent, `a` et `j` apparaissent 7 fois chacun.

### Ces résultats dépendent beaucoup de la convention. Compter la ponctuation ou classer les appels comme opérateurs changerait tout.

## 2.7 Validité des métriques de Halstead

---

### Définition d'une mesure valide (Définition du cours)

Une mesure $M : A \to B$ est **valide** par rapport à un système empirique $E = (A, \{R_1, \dots, R_n\})$ si toute relation empirique entre deux entités se retrouve entre leurs mesures.

$$\forall (a, b) \in R,\ (M(a), M(b)) \in S$$

Si un programme `a` est réellement plus complexe qu'un programme `b`, il faut donc que $M(a) > M(b)$. Cela suppose que $M$ associe une seule valeur à chaque programme et que l'ordre des valeurs respecte celui réellement constaté.

---

### 1. Le comptage dépend d'une convention arbitraire

La frontière entre opérateur et opérande n'est pas fixée. Rien n'oblige à compter la ponctuation ou les types, et sur le même `iqsort0` les résultats changent beaucoup.

| Mesure        | Ponctuation non comptée (2.6) | Ponctuation comptée |
| ------------- | :---------------------------: | :-----------------: |
| $n_t$ / $N_t$ |            13 / 22            |       17 / 48       |
| Volume V      |            250,36             |       385,44        |
| Difficulté D  |             28,44             |        37,19        |
| Effort E      |           7 119,67            |      14 333,55      |

### Un même programme n'a donc pas une valeur unique. Selon la personne qui mesure, l'effort varie du simple au double. $M$ n'est alors pas une application bien définie et la première condition de validité n'est pas garantie.

### La convention peut même inverser l'ordre réel. `(a + j) + 1` n'est pas plus compliqué que `a + j + 1`, pourtant si on compte les parenthèses $N$ et $V$ augmentent. Pareil pour `int i, j;` et `int i; int j;` qui ne donnent pas le même $N_t$.

---

### 2. Les formules ne reposent pas sur des relations empiriques démontrées

Les comptages et la longueur $N$ restent intuitifs, un programme plus long a plus de symboles. Par contre aucune expérience ne justifie les formules du volume, de la difficulté et de l'effort. Pourquoi un $\log_2$, pourquoi diviser $n_t$ par 2 ?

### Or une relation empirique doit reposer sur des preuves vérifiables. Sans elles, rien ne dit qu'un programme avec un $D$ plus grand est vraiment plus dur à comprendre.

---

### Les métriques de Halstead sont donc difficiles à justifier à deux niveaux, le comptage et les formules. On ne peut pas garantir que l'ordre qu'elles donnent entre deux programmes correspond à leur vraie complexité, ce qui met en doute leur validité. C'est pour ça qu'on les utilise rarement seules, plutôt combinées à d'autres mesures comme dans le MI. (Basé sur l'analyse précédente et le cours)

## 2.9 Points de fonction du QuickSort

---

### Poids

Chaque poids vaut la base de la catégorie multipliée par le niveau, 1 pour simple, 2 pour moyen et 3 pour difficile.

| Catégorie         | Base | Justification                                              |
| ----------------- | :--: | ---------------------------------------------------------- |
| Entrées externes  |  1   | Recevoir une donnée, c'est notre référence             |
| Requêtes externes |  1   | Une entrée suivie d'une réponse immédiate, sans traitement |
| Sorties externes  |  2   | Le résultat doit être calculé avant d'être fourni          |
| Fichiers externes |  2   | Accès à des données via un mécanisme externe               |
| Fichiers internes |  3   | Structure de données à concevoir et à maintenir            |

### Scores pour `iqsort0`

- Deux entrées externes, `n` qui est simple et le tableau `a` qui est moyen.
- Une sortie externe difficile, le tableau trié, qui demande toute la partition et la récursion.
- Pas de requête ni de fichier, tout se fait en mémoire.

### $$UFC = 1 \times 1 + 2 \times 1 + 6 \times 1 = \mathbf{9}$$

### Le score est très faible alors que l'algorithme n'est pas si simple. Les points de fonction ne regardent que les échanges avec l'extérieur, ils sont donc peu adaptés au QuickSort dont toute la difficulté est interne.

## 2.10 Index de Maintenabilité (MI)

---

### Valeurs utilisées pour `iqsort0`

| Mesure                       | Valeur | Source                                |
| ---------------------------- | :----: | ------------------------------------- |
| Volume d'Halstead (HV)       | 250,36 | Onglet Halstead (2.6)                 |
| Complexité cyclomatique (CC) |   4    | Onglet CC (2.5)                       |
| Lignes de code (LOC)         |   12   | `loc.sh` sur le code de `iqsort0`     |
| Commentaires (COM)           |  0 %   | Le code ne contient aucun commentaire |

### Calcul

$$MI = 171 - 5{,}2 \ln(HV) - 0{,}23\,CC - 16{,}2 \ln(LOC) + 50 \sin\sqrt{2{,}46 \times COM}$$

$$MI = 171 - 28{,}72 - 0{,}92 - 40{,}26 + 0 = \mathbf{101{,}11}$$

### On dépasse le haut de l'échelle de 1 à 100, la fonction est donc très facile à maintenir. Elle est courte et peu complexe, et sans commentaire le dernier terme vaut 0.

## 2.11 MI du code commenté

---

### Le code commenté se trouve dans [`src/iqsort0.c`](src/iqsort0.c).

| Mesure                       | Code initial | Code commenté | Remarque                                                    |
| ---------------------------- | :----------: | :-----------: | ----------------------------------------------------------- |
| Volume d'Halstead (HV)       |    250,36    |    250,36     | Les commentaires ne sont ni des opérateurs ni des opérandes |
| Complexité cyclomatique (CC) |      4       |       4       | Le graphe de flot de contrôle ne change pas                 |
| Lignes de code (LOC)         |      12      |      26       | `./loc.sh src`                                              |
| Commentaires (COM)           |     0 %      |    53,85 %    | 14 lignes de commentaire sur 26                             |
| **MI**                       |  **101,11**  |  **134,24**   |                                                             |

$$MI = 171 - 28{,}72 - 0{,}92 - 16{,}2 \ln(26) + 50 \sin\sqrt{2{,}46 \times 0{,}5385} = 171 - 28{,}72 - 0{,}92 - 52{,}78 + 45{,}66 = \mathbf{134{,}24}$$

### COM est pris comme un ratio entre 0 et 1, c'est ce que stocke le tableur dans une cellule en pourcentage.

### Les commentaires font gagner environ 33 points. Leur bonus (+45,66) compense largement les lignes en plus (−52,78 au lieu de −40,26). Par contre le MI ne regarde que la quantité de commentaires, pas leur qualité.

## 2.12 Facteur de complexité technique (TFC)

---

### On a choisi I-AMU_Web_APP, notre application web qui donne aux étudiants un accès encadré à un LLM local. Elle tourne sous Docker avec PHP, PostgreSQL et Ollama et compte 524 commits sur GitHub.

### Chaque facteur est noté de 0 à 5 selon son influence.

| #   | Facteur technique                               | Score | Justification                                                       |
| --- | ----------------------------------------------- | :---: | ------------------------------------------------------------------- |
| F1  | Sauvegarde et récupération fiables              |   3   | Données importantes mais juste un volume Docker, pas de vraie sauvegarde |
| F2  | Communications de données                       |   4   | HTTP, appels à l'API d'Ollama et envoi de mails                     |
| F3  | Traitement distribué                            |   3   | Application, base et LLM dans des conteneurs séparés                |
| F4  | Performances critiques                          |   3   | Le LLM doit répondre vite pendant les séances                       |
| F5  | Environnement existant et fortement utilisé     |   2   | Prévue pour les serveurs d'AMU mais isolée dans Docker              |
| F6  | Entrées de données en ligne                     |   5   | Tout est saisi en ligne                                             |
| F7  | Entrées sur plusieurs écrans ou opérations      |   3   | Inscription avec validation de l'email, création et accès aux sessions |
| F8  | Fichiers maîtres mis à jour en ligne            |   4   | La base est mise à jour à chaque message                            |
| F9  | Entrées, sorties, fichiers ou requêtes complexes |   3   | Import de PDF, export JSON, requêtes au LLM avec contexte           |
| F10 | Traitement interne complexe                     |   3   | 5 rôles, cycle de vie des sessions, adaptateurs LLM                 |
| F11 | Code réutilisable                               |   3   | MVC + Domain et adaptateur LLM interchangeable                      |
| F12 | Conversion et installation prévues              |   4   | Docker Compose et scripts SQL testés en CI                          |
| F13 | Installations multiples dans plusieurs organisations |   2   | Domaines email configurables mais pensée pour AMU               |
| F14 | Facilité de changement et d'utilisation         |   4   | Modèles et domaines configurables sans toucher au code, guide utilisateur |
|     | **Total ΣF**                                    | **46** |                                                                    |

$$TFC = 0{,}65 + 0{,}01 \times \sum_{i=1}^{14} F_i = 0{,}65 + 0{,}01 \times 46 = \mathbf{1{,}11}$$

### Le TFC va de 0,65 à 1,35. Avec 1,11 I-AMU est un peu au-dessus de la moyenne, ça ajouterait 11 % aux points de fonction. Ce sont surtout la saisie en ligne et la base mise à jour en continu qui pèsent, c'est classique pour une application web.

## 2.13 Mesures du projet r201DOOEngins-ENS

---

### Le dépôt [IUTInfoAix-R2-01/r201DOOEngins-ENS](https://github.com/IUTInfoAix-R2-01/r201DOOEngins-ENS) est un exercice Java de R2.01 avec 11 fichiers, dont un fichier de tests JUnit.

### On a utilisé `loc.sh` pour le LOC, [lizard](https://github.com/terryyin/lizard) pour la complexité cyclomatique et [multimetric](https://github.com/priv-kweihmann/multimetric) pour Halstead. Le MI est recalculé avec la formule du cours, celui de multimetric n'utilise pas la même.

| Mesure | Valeur |
| --- | :---: |
| LOC (dossier `src`) | 548 |
| Méthodes | 58 |
| CC totale / maximale | 68 / 4 |
| Halstead $n_t$ / $N_t$ / $n_d$ / $N_d$ | 71 / 1241 / 131 / 739 |
| Volume V | 15 163,26 |
| Difficulté D | 200,26 |
| Effort E | 3 036 645 |
| COM | 11,68 % |
| MI moyen par fichier | 104,18 |
| MI du projet entier | 28,68 |
| UFC | 15 |
| TFC | 0,74 |

### Presque toutes les méthodes ont une CC de 1. Les plus complexes sont `Carburant.nom` et `Carburant.getConso` avec un `switch` à 4 chemins.

### multimetric compte la ponctuation dans les opérateurs, ses chiffres Halstead ne sont donc pas comparables à ceux de la 2.6.

### Le MI se calcule normalement fichier par fichier. Sur le projet entier, le LOC et le volume sont tellement grands que le score tombe à 28, ce qui ne veut pas dire grand-chose. Le fichier de tests est le moins maintenable avec 45,57, les autres fichiers sont autour de 100.

### Pour l'UFC on reprend les poids de la 2.9. Il y a trois entrées (la masse, le carburant et la propulsion d'un engin), trois sorties (la consommation, le message de conduite et la description) et trois requêtes (consulter un engin, une propulsion ou les carburants), ce qui donne 15.

### Pour le TFC presque tous les facteurs sont à 0, il n'y a ni base, ni réseau, ni interface. Seuls la réutilisabilité (3), la facilité de changement (3), les entrées-sorties (1), le traitement (1) et l'installation (1) comptent, soit une somme de 9.

## 2.14 Couplage et absence de cohésion

---

### Le comptage est fait à la main sur les 11 classes de r201DOOEngins-ENS, en suivant les définitions du cours.

### Couplage (CBO)

### Deux classes sont couplées quand l'une lit ou écrit une variable de l'autre ou appelle une de ses méthodes, constructeurs compris. Pour un appel polymorphe on compte toutes les implémentations possibles, par exemple `getPropulsion().consommerEnergie()` couple `Roulant` à `Propulsion`, `Thermique`, `Electrique` et `Eolienne`. Les simples déclarations de type et les classes de Java comme `String` ne comptent pas.

| Classe | CBO |
| --- | :---: |
| Carburant | 3 |
| Propulsion | 6 |
| Electrique | 5 |
| Eolienne | 4 |
| Thermique | 6 |
| Engin | 4 |
| Roulant | 7 |
| Flottant | 7 |
| Main | 6 |
| Marker | 0 |
| ExamEnginsTest | 8 |

### Le CBO moyen est de 5,09. `Roulant` et `Flottant` sont les plus couplées à cause du polymorphisme, et `Marker` n'est utilisée par personne, c'est du code mort.

### Absence de cohésion (LCOM)

### Pour chaque classe on compte les paires de méthodes qui ne partagent aucun attribut (P) et celles qui en partagent au moins un (Q). LCOM vaut P − Q, ramené à 0 s'il est négatif. On prend les méthodes qui ont un corps, constructeurs compris.

| Classe | Méthodes | P | Q | LCOM |
| --- | :---: | :---: | :---: | :---: |
| Carburant | 3 | 2 | 1 | 1 |
| Propulsion | 0 | 0 | 0 | 0 |
| Electrique | 9 | 20 | 16 | 4 |
| Eolienne | 2 | 1 | 0 | 1 |
| Thermique | 9 | 16 | 20 | 0 |
| Engin | 6 | 10 | 5 | 5 |
| Roulant | 2 | 1 | 0 | 1 |
| Flottant | 2 | 1 | 0 | 1 |
| Main | 1 | 0 | 0 | 0 |
| Marker | 0 | 0 | 0 | 0 |
| ExamEnginsTest | 24 | 276 | 0 | 276 |

### `Thermique` est la classe la plus cohésive, presque toutes ses méthodes touchent `masse` ou `carburant`. `Engin` et `Electrique` ont beaucoup de getters et setters qui ne touchent chacun qu'un attribut, ce qui fait monter leur LCOM. La classe de tests a un LCOM énorme mais c'est normal, chaque test est indépendant et n'utilise aucun attribut.

# TP2 Mesures d'impact environnemental

## 1.1 Simulations de physique des particules

---

### On reprend l'expérience Geant4 de l'article Green Algorithms (Lannelongue et al., 2021). Une expérience dure 3 semaines sur un Xeon E5-2680 avec 24 threads sur 12 cœurs et 10 Go de mémoire.

| Paramètre | Valeur | Source |
| --- | :---: | --- |
| t | 504 h | 3 semaines |
| nc × Pc | 12 × 10 W | Xeon E5-2680 v3, 120 W de TDP pour 12 cœurs |
| uc | 1 | Valeur par défaut du cours |
| nm × Pm | 10 × 0,3725 W | Mémoire |
| PUE | 1,67 | Moyenne mondiale |
| CI | 475 gCO2e/kWh | Moyenne mondiale |

$$E = t \times (n_c \times P_c \times u_c + n_m \times P_m) \times PUE \times 0{,}001 = 504 \times (120 + 3{,}725) \times 1{,}67 \times 0{,}001 = \mathbf{104{,}14\ kWh}$$

$$C = E \times CI = 104{,}14 \times 475 = \mathbf{49{,}47\ kgCO_2e}$$

### Vérification avec le site Green Algorithms

### Avec ses valeurs par défaut le calculateur donne 97,28 kWh et 46,69 kg, parce qu'il utilise maintenant un PUE de 1,56 et une intensité carbone mondiale de 480. En remettant 1,67 et 475 on retrouve exactement 104,14 kWh et 49,47 kg, comme les 49 465 g de l'article. Le E5-2680 n'est plus dans la liste du site, on a donc saisi ses caractéristiques à la main.

### Les 11 niveaux d'énergie

### Chaque niveau d'énergie est une expérience complète de 3 semaines. On l'intègre avec le facteur d'échelle pragmatique PSF = 11, ce qui donne 49,47 × 11 = 544,12 kgCO2e pour toute l'étude. Le site donne la même valeur avec un facteur multiplicatif de 11, et l'article annonce 544 115 g.

### Absorption par un arbre

### Un arbre adulte absorbe environ 11 kg de CO2 par an. Il lui faut donc 4,5 ans pour une seule expérience et 49,5 ans pour toute l'étude, soit environ 593 mois-arbres comme dans l'article.

## 1.2 IA, traitement automatique des langues

---

### L'entraînement de BERT demande 79 h sur 64 GPU Tesla V100 utilisés à 62,7 %. On compte 300 W par V100, et pas de mémoire car l'article ne la prend pas en compte pour cet exemple.

| Paramètre | Valeur |
| --- | :---: |
| t | 79 h |
| nc × Pc | 64 × 300 W |
| uc | 0,627 |
| PUE | 1,67 |
| CI | 475 gCO2e/kWh |

$$E = 79 \times (64 \times 300 \times 0{,}627) \times 1{,}67 \times 0{,}001 = \mathbf{1\,588{,}23\ kWh}$$

$$C = 1\,588{,}23 \times 475 = \mathbf{754{,}41\ kgCO_2e}$$

### On retrouve les 754 407 g de l'article. Il faudrait 68,6 ans à un arbre pour absorber un seul entraînement.

### Avec un PSF de 100

### La recherche des hyperparamètres oblige à relancer l'entraînement de nombreuses fois. Avec un PSF de 100 on obtient 754,41 × 100 = 75 440,74 kgCO2e, soit environ 75,4 tonnes, comme les 75 440 740 g de l'article.

### Sur le site Green Algorithms la version actuelle des données compte 250 W par V100 et donne 628,67 kg. En choisissant la version v2.0 des données, qui compte 300 W, le site retrouve exactement 754,41 kg.

## 2.1 Formule de l'EcoIndex dans le code de cnumr

---

### La formule du cours est la suivante.

$$EcoIndex = 100 - 5 \times \frac{3 \times Q(DOM) + 2 \times Q(requêtes) + Q(taille)}{6}$$

$$Q(x) = (n - 1) + \frac{x - borneInf(n)}{borneSup(n) - borneInf(n)}$$

### On a parcouru les projets de cnumr qui calculent l'EcoIndex.

| Projet | Langage | Formule du cours | Remarque |
| --- | :---: | :---: | --- |
| [EcoIndex_python](https://github.com/cnumr/EcoIndex_python) | Python | Oui | Score arrondi à l'entier, utilisé par l'API Ecoindex |
| [ecoindex_js](https://github.com/cnumr/ecoindex_js) | JavaScript | Oui | Score non arrondi |
| [ecoindex_node](https://github.com/cnumr/ecoindex_node) | JavaScript | Oui | Score arrondi à l'entier |
| [GreenIT-Analysis](https://github.com/cnumr/GreenIT-Analysis) | JavaScript | Oui | Bornes écrites en dur dans le code |
| [lighthouse-plugin-ecoindex](https://github.com/cnumr/lighthouse-plugin-ecoindex) | TypeScript | Oui | Reprend le code de ecoindex_js |
| [EcoIndex_BFF](https://github.com/cnumr/EcoIndex_BFF) | Go | Pas de calcul | Relaie les requêtes vers l'API Ecoindex |

### Partout on retrouve les poids 3, 2 et 1 et la même fonction quantile. Le code cherche le premier intervalle qui contient la valeur, prend son numéro moins 1 et ajoute la position de la valeur entre les deux bornes, exactement comme dans le cours. Au-delà de la dernière borne le quantile est bloqué à 20.

### Les 21 bornes de chaque critère sont identiques à celles du dépôt [ecoindex_reference](https://github.com/cnumr/ecoindex_reference), même quand elles sont recopiées en dur.

### Les seules différences portent sur l'arrondi. Certains projets arrondissent le score à l'entier et d'autres non. Pour les gaz à effet de serre et l'eau, tous utilisent les formules du cours $2 + 2 \times (50 - EcoIndex)/100$ et $3 + 3 \times (50 - EcoIndex)/100$, arrondies à deux décimales.
