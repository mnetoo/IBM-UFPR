module Impares where

-- Questão 2

ehImpar :: Int -> Bool
ehImpar x
    | mod x 2 == 0 = False
    | otherwise = True

removerImpares :: (Int -> Bool) -> [Int] -> [Int]
removerImpares _ [] = []
removerImpares f (h:t)
    | f h == True = h : removerImpares f t
    | otherwise = removerImpares f t