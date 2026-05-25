module ListasTuplas where

-- Operações com Listas
somarLista :: [Int] -> Int
somarLista [] = 0
somarLista (h:t) = h + somarLista t

removerPares :: [Int] -> [Int]
removerPares [] = []
removerPares (h:t)
    | par == 0 = removerPares t 
    | otherwise = h: removerPares t
    where
        par = mod h 2

inverterLista :: [Int] -> [Int]
inverterLista [] = []
inverterLista (h:t) = inverterLista t ++ [h]

nomesA :: [String] -> [String]
nomesA [] = []
nomesA (h:t) = 
    if(head h == 'A') then h: nomesA t
    else nomesA t

-- -----------------------------------------------------------------

-- Listas por Compreensão
multiplos3 :: [Int]
multiplos3 = [x | x <- [1..15], mod x 3 == 0]

listaDupla :: [[Int]]
listaDupla = [[x] | x <- [1..5]]

-- -----------------------------------------------------------------

-- Tuplas
calcula :: Int -> (Int, Int, Int, Int)
calcula x
    | x == 0 = (0,0,0,0)
    | otherwise = (2 * x, 3 * x, 4 * x, 5 * x)

verifica :: Int -> (Int, String)
verifica x =
    if(x == 0) then (0, "PAR")
    else if(mod x 2 == 0) then (div x 2, "PAR")
    else (div x 2, "IMPAR")

somaProduto :: [Int] -> (Int, Int)
somaProduto [] = (0,0)
somaProduto (h:t)
    | x <= 0 = somar