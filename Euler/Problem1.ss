(define % modulo)

(define (find-sum i sum)
	(if
		(> 1000 i)
		(find-sum
			(+ i 1)
			(if
				(or (= (% i 3) 0) (= (% i 5) 0))
				(+ sum i)
				sum))
		sum))

(display (find-sum 1 0))
