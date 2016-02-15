(require (lib "list.ss" "srfi" "1"))

(define (find-diff set)
  (abs
   (-
    (fold + 0 (map (lambda (x) (expt x 2)) set))
    (expt (fold + 0 set) 2))))

(display (find-diff (iota 100 1)))
