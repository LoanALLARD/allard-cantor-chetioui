/*
 * Auteur      : Loan ALLARD (d'après Bentley et McIlroy, 1993)
 * Date        : 16/10/2026
 * Description : tri rapide (QuickSort) simplifié. Trie par ordre croissant,
 *               en place, les n premiers entiers du tableau a, en prenant
 *               le premier élément comme pivot.
 */
void iqsort0(int *a, int n)
{
  int i, j;
  /* Cas d'arrêt : un tableau de 0 ou 1 élément est déjà trié */
  if (n <=1)
    return;
  /* Partition : on parcourt le tableau à partir du 2e élément.
     a[1..j] contient les éléments déjà vus plus petits que le pivot a[0] */
  for (i = 1, j = 0; i < n; i++)
    /* Un élément plus petit que le pivot est ajouté à la fin de cette zone */
    if (a[i] < a[0])
      swap(++j, i, a);
  /* Le pivot est placé à sa position définitive, entre les deux zones */
  swap(0, j, a);
  /* Tri récursif de la partie gauche : les j éléments plus petits que le pivot */
  iqsort0(a, j);
  /* Tri récursif de la partie droite : les éléments supérieurs ou égaux au pivot */
  iqsort0(a+j+1, n-j-1);
}
