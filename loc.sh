# Utilisation : ./loc.sh [dossier] (par défaut : dossier courant)

dir="${1:-.}"
total=0
nb_fichiers=0

while IFS= read -r -d '' f; do
    # ignore les fichiers binaires (images, zip, etc.)
    grep -Iq . "$f" || continue
    n=$(wc -l < "$f")
    printf "%8d  %s\n" "$n" "$f"
    total=$((total + n))
    nb_fichiers=$((nb_fichiers + 1))
done < <(find "$dir" -type f -not -path '*/.git/*' -print0)

echo "----------------------------------------"
echo "Fichiers : $nb_fichiers"
echo "Total LOC : $total"
