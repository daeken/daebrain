(define (find-max num)
  (define top (integer-sqrt num))
  (if (zero? (modulo top 2)) (+ top 1) top))

(define (find-fac num div)
  (if
   (<= div 2)
   (if
    (zero? (modulo num 2))
    2
    1)
   (if
    (and (zero? (modulo num div)) (= (find-fac div (find-max div)) 1))
    div
    (find-fac num (- div 2)))))
  
(define num 600851475143)
(display (find-fac num (find-max num)))
