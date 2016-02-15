(define (palindrome? num)
  (= num (string->number (list->string (reverse (string->list (number->string num)))))))
(define (find-largest x y largest)
  (define num (* x y))
  (if
   (and (= x 999) (= y 999))
   largest
   (find-largest
    (+ x (quotient (+ y 1) 1000))
    (modulo (+ y 1) 1000)
    (if
     (and (palindrome? num) (> num largest))
     num
     largest))))
(display (find-largest 1 1 0))
