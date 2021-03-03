# mpsh
Projet C & Système (L3 Informatique, Université Paris Diderot)

Félix Desmaretz ([firgaty](http://moule.informatique.univ-paris-diderot.fr:8080/u/firgaty)) + Louis Gavalda ([lgaval98](http://moule.informatique.univ-paris-diderot.fr:8080/u/lgaval98))

## Instruction :

Lancez la commande `source setup.sh` pour compiler et ajouter ce dossier à votre `$PATH` puis appelez `mpsh`;
 
## Documentation :

Avec le paquet `doxygen` commenter le code avec les différents mots clés Doxigen ([tuto](https://franckh.developpez.com/tutoriels/outils/doxygen)) mais en utilisant des `@` au lieu de `\` pour la lisibilité. Exemple :

```c
/**
 * @brief Copies the environment main to copy.
 *
 * @param main Environment to copy from.
 * @param copy Environment to copy to.
 */
void env_copy(env_t *main, env_t *copy) {
  map_str_copy(main->aliases, copy->aliases);
  map_str_copy(main->vars, main->vars);
}
```

Puis on peut générer la doc avec

```bash
$ doxygen Doxyfile
```

La doc est générée en `HTML` dans `docx/html` il suffit alors de lire avec un navigateur `docx/html/index.html`. C'
