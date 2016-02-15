(require (lib "list.ss" "srfi" "1"))

(define (square x) (expt x 2))
(define (correct? total i)
  (let
      ((a (modulo i 1000))
       (b (modulo (quotient i 1000) 1000))
       (c (quotient i 1000000)))
    (and (= total (+ a (+ b c)))
         (= (square c) (+ (square a) (square b))))))

(define (find-triplet total i)
  (if (> i 1000000000)
      -1
      (if (correct? total i)
          i
          (find-triplet total (+ i 1)))))

(display (find-triplet 1000 0))
