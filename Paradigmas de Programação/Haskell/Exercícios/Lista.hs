module Lista where

-- Questão 3

ehPar :: Int -> Bool
ehPar x
    | mod x 2 == 0 = True
    | otherwise = False

dobraValor :: Int -> Int
dobraValor x = x * 2

processaLista :: [Int] -> (Int -> Int) -> (Int -> Bool) -> [Int]
processaLista [] _ _ = []
processaLista (h:t) f1 f2
    | f2 h == True = (f1 h) : processaLista t f1 f2
    | otherwise = h : processaLista t f1 f2