module FuncoesRecursivas where

fibonacci :: Int -> Int
fibonacci x
    | x == 0 = 0
    | x == 1 = 1
    | otherwise = fibonacci (x -1) + fibonacci(x - 2)

contaDigitos :: Int -> Int
contaDigitos x =
    if(x < 10) then 1
    else 1 + contaDigitos(div x 10)

somaDigitos :: Int -> Int
somaDigitos x
    | x == 0 = 0
    | otherwise = (mod x 10) + somaDigitos(div x 10)