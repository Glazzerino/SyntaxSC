lambda 
else
true  false   nil
car  cdr  cons  list

apply map

let begin

null? eq?

set!

 

defines

 

-

< 

> 

>=

=

<> 

 'abc

 

(define (cuadrado x)

  (* x x))




(define (area-circulo r)

  (* 3.1416 (cuadrado r)))




(define (area-cilindro radio altura)

   (+ (* 2 (área-circulo radio)

        (* (* 2 314.16E-2 radio) altura))))




(define (cuantos n)  ; define la cantidad de dígitos de un entero

  (if (<= n 9) 1

    (+ (cuantos (/ n 10)) 1)))




1idvalido;



esto es una prueba ;
esto es una prueba;
; errores

#id_invalido

123.5.6

=[3+5.8)
