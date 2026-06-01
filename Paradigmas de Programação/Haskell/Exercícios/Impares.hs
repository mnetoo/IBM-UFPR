module Impares where

-- Questão 2
-- Escreva uma função recursiva pura chamada removerImpares que receba uma lista de números inteiros ([Int]) e retorne uma nova lista contendo apenas 
-- os números pares. Restrição: Não é permitido o uso de geradores de lista ou de funções utilitárias nativas do módulo Prelude (como filter).

ehImpar :: Int -> Bool
ehImpar x
    | mod x 2 == 0 = False
    | otherwise = True

removerImpares :: (Int -> Bool) -> [Int] -> [Int]
removerImpares _ [] = []
removerImpares f (h:t)
    | f h == True = h : removerImpares f t
    | otherwise = removerImpares f t