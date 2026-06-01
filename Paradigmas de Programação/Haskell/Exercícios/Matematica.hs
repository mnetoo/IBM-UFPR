module Matematica where

-- a) Uma função ehMultiploDe3 :: Int -> Bool que verifique se um número é múltiplo de 3.
ehMultiplo3 :: Int -> Bool
ehMultiplo3 x = 
    if(mod x 3 == 0) then True
    else False

-- b) Uma função ehMultiploDe5 :: Int -> Bool que verifique se um número é múltiplo de 5.
ehMultiplo5 :: Int -> Bool
ehMultiplo5 x = 
    if(mod x 5 == 0) then True
    else False

-- c) Uma função de alta ordem e recursiva chamada filtrarMultiplos :: [Int] -> (Int -> Bool) -> [Int] que receba uma lista de inteiros e uma das 
-- funções definidas em (a) ou (b), retornando apenas os elementos que satisfaçam a condição.
filtrarMultiplos :: [Int] -> (Int -> Bool) -> [Int]
filtrarMultiplos [] _ = []
filtrarMultiplos (h:t) f =
    if(f h) then h : filtrarMultiplos t f
    else filtrarMultiplos t f