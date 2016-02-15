(require (lib "list.ss" "srfi" "1"))

(define (divisible? num top list)
  (if
   (> (car list) top)
   #f
   (if
    (zero? (modulo num (car list)))
    #t
    (divisible? num top (cdr list)))))

(define (sum-primes max i primes)
  (if
   (>= i max)
   (fold + 0 primes)
   (sum-primes
    max
    (+ i 2)
    (if
     (divisible? i (sqrt i) primes)
     primes
     (cons i primes)))))

(display (sum-primes 2000000 3 '(2)))
