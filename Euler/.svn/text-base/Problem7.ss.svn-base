(define (prime? i primes)
  (if
   (null? primes)
   #t
   (if
    (zero? (modulo i (car primes)))
    #f
    (prime? i (cdr primes)))))

(define (nth-prime n i primes)
  (if
   (= (length primes) n)
   (car (reverse primes))
   (nth-prime
    n
    (+ i 2)
    (if
     (prime? i primes)
     (reverse (cons i (reverse primes)))
     primes))))

(display (nth-prime 10001 3 '(2)))
