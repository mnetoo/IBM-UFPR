module FuncoesRecursivas where

-- a. Escreva uma função recursiva que gere o n-ésimo termo da sequência de
-- Fibonacci usando recursão. Dica: a função retorna 0 quando n é igual a 0; 1
-- quando n é igual a 1; e a soma dos dois termos anteriores do n-éstimo termo.
fibonacci :: Int -> Int
fibonacci x
    | x == 0 = 0
    | x == 1 = 1
    | otherwise = fibonacci (x -1) + fibonacci(x - 2)

-- b. Escreva uma função recursiva que conte o número de dígitos de um número
-- inteiro. Considere que o número digitado como entrada é sempre maior que zero.
contaDigitos :: Int -> Int
contaDigitos x =
    if(x < 10) then 1
    else 1 + contaDigitos(div x 10)

-- c. Escreva uma função recursiva que calcule a soma dos dígitos de um número
-- inteiro. Considere que o número digitado como entrada é sempre maior que zero.
somaDigitos :: Int -> Int
somaDigitos x
    | x == 0 = 0
    | otherwise = (mod x 10) + somaDigitos(div x 10)