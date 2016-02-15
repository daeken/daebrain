(define (sum-fib a b sum)
  (if
      (<= b 4000000)
      (sum-fib 
               b
               (+ a b)
               (if (zero? (modulo b 2))
                   (+ sum b)
                   sum))
      sum))

(display (sum-fib 1 1 0))
