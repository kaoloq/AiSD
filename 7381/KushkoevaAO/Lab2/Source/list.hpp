namespace h_list {                                      //создание структуры иерархического списка
        struct s_expr;
        struct  two_ptr {
                s_expr *head;                                   //указатель на начало списка
                s_expr *tail;                                   //указатель на конец списка
        };

        struct s_expr {
                bool test;                                      // если true: atom, иначе false: pair
                union {
                        char atom;
                        two_ptr pair;
                } node;
        };
        typedef s_expr *lisp;


        lisp head(const lisp s);
        lisp tail(const lisp s);
        lisp cons(const lisp h, const lisp t);
        lisp make_atom(const char x);
        bool isAtom(const lisp s);
        bool isNull(const lisp s);
        void destroy(lisp s);
        char getAtom(const lisp s);
        void read_lisp(lisp& y);
        void read_s_expr(char prev, lisp& y);
        void read_seq(lisp& y);
        void write_lisp(const lisp x);
        void write_seq(const lisp x);
        lisp copy_lisp(const lisp x);
}
