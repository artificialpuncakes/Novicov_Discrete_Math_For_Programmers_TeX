// TODO
vector* find_strongly_connected_components(int p, list **G) {
  vector *out = vector_create();
  int k = 0; /* количество элементов в текущем независимом множестве */
  list *S[p]; /* S[k] — независимое множество из к вершин */
  list *Q_minus[p];
  list *Q_plus[p];
  S[k] = list_create();
  Q_minus[k] = list_create();
  Q_plus[k] = list_create();

  for (int v = 0; v < p; v++) {
    if (v != 0) {
      S[v] = list_create();
      Q_minus[v] = list_create();
      Q_plus[v] = list_create();
    }
    list_add(Q_plus[k], v);
  }

  label: M1; /* шаг вперёд */
    int v = list_pop_back(Q_plus[k]); /* расширяющая вершина */
    list *buf = list_copy(S[k]);
    S[k+1] = buf; list_push_back(S[k + 1], v);
    Q_minus[k+1] = list_difference(Q_minus[k], G[v]);
    list_push_back(G[v], v);
    Q_plus[k+1] = list_difference(Q_plus[k], G[v]);
    list_pop_back(G[v]);
    k++;
  label: M2;
    list_node *iter = Q_minus[k]->head;
    while (iter != NULL) {
      int u = iter->v;
      list *buf = list_intersection(G[u], Q_plus[k]);
      if (list_size(buf) == 0) {
        goto M3; /* можно возвращаться */
      }
    }
    if (list_size(Q_plus[k]) == 0) {
      if (list_size(Q_minus[k]) == 0) {
        vector_push_back(out, S[k]); /* множество S[k] максимально */
      }
      goto M3; /* можно возвращаться */
    }
    else {
      goto M1; /* можно идти вперёд */
    }
  label: M3; /* шаг назад */
    k = k - 1;
    int v = list_pop_back(S[k]);
    list_push_back(Q_minus[k], v); /* вершина v уже добавлялась */
    list_remove(Q_plus[k], v);
    if (k == 0 && list_size(Q_plus[k]) == 0) {
      return out; /* перебор завершён */
    }
    else {
      goto M2; /* переход на проверку */
    }
}
