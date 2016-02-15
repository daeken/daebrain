(require (lib "list.ss" "srfi" "1"))

(define (divisible? num list)
  (if
   (null? list)
   #t
   (if
    (zero? (modulo num (car list)))
    (divisible? num (cdr list))
    #f)))

(define (find-smallest i list)
  (if
   (divisible? i list)
   i
   (find-smallest (+ i 20) list)))

(display (find-smallest 20 (iota 20 1)))
