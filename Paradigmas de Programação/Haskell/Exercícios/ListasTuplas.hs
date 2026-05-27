module ListasTuplas where

-- 1) Escreva uma função recursiva que some todos os elementos de uma lista de inteiros.
somarLista :: [Int] -> Int
somarLista [] = 0
somarLista (h:t) = h + somarLista t

-- 2) Escreva uma função recursiva que remova todos os números pares de uma lista de inteiros.
removerPares :: [Int] -> [Int]
removerPares [] = []
removerPares (h:t)
    | par == 0 = removerPares t 
    | otherwise = h: removerPares t
    where
        par = mod h 2

-- 3) Escreva uma função recursiva que inverta os elementos de uma lista de números reais.
inverterLista :: [Int] -> [Int]
inverterLista [] = []
inverterLista (h:t) = inverterLista t ++ [h]

-- 4) Escreva uma função recursiva que receba uma lista de nomes e retorne outra lista
-- apenas com os nomes que começam com a letra A. Dica: utilize a função head do
-- módulo Prelude para pegar a primeira letra de um nome.
nomesA :: [String] -> [String]
nomesA [] = []
nomesA (h:t) = 
    if(head h == 'A') then h: nomesA t
    else nomesA t

-- -----------------------------------------------------------------

-- 1) Defina as seguintes listas por compreensão
multiplos3 :: [Int]
multiplos3 = [x | x <- [1..15], mod x 3 == 0]

listaDupla :: [[Int]]
listaDupla = [[x] | x <- [1..5]]

-- -----------------------------------------------------------------

-- 1) Faça uma função que receba um inteiro e retorne uma tupla, contendo: o dobro deste
-- número na primeira coordenada, o triplo na segunda, o quádruplo na terceira e o
-- quíntuplo na quarta.
calcula :: Int -> (Int, Int, Int, Int)
calcula x
    | x == 0 = (0,0,0,0)
    | otherwise = (2 * x, 3 * x, 4 * x, 5 * x)

-- 2) Faça uma função que receba um número inteiro n1 e retorne uma tupla contendo o
-- resultado da divisão inteira desse número por dois e uma string indicando se n1 é par ou ímpar.
verifica :: Int -> (Int, String)
verifica x =
    if(x == 0) then (0, "PAR")
    else if(mod x 2 == 0) then (div x 2, "PAR")
    else (div x 2, "IMPAR")

-- 3) Faça uma função recursiva que receba uma lista de números inteiros (positivos e
-- negativos) e retorne uma tupla contendo a soma dos números positivos e o produto
-- dos números negativos.
somaProduto :: [Int] -> (Int, Int)
somaProduto [] = (0,0)
somaProduto (h:t)
    | h >= 0 = (h + soma, produto)
    | otherwise = (soma, h * produto)
    where
        (soma, produto) = somaProduto t

-- 4) Escreva uma função que receba uma lista dos pontos turísticos de Curitiba e uma
-- avaliação qualquer fornecida no intervalo de 0 a 10. Cada ponto turístico é formado por
-- um nome, uma nota de avaliação e um tipo (ex.: Barigui, 10, parque). A função deve
-- retornar uma lista com os nomes e avaliação dos pontos turísticos de Curitiba que
-- possuem nota acima de um valor de referência fornecido e que sejam parques ou museus.
type NomePonto = String
type NotaPonto = Int
type TipoPonto = String
type Ponto = (NomePonto, NotaPonto, TipoPonto)
type PontoTuristicos = [Ponto]

pontoTuristicos :: PontoTuristicos -> NotaPonto -> [(NomePonto, NotaPonto)]
pontoTuristico [] _ = []
pontoTuristico ((nome, nota, tipo):t) n
    | nota >= n && tipo == "parque" || tipo == "museu" = (nome, nota) : pontoTuristico t n
    | otherwise = pontoTuristico t n 

pontos :: PontosTuristicos -> NotaPonto -> [(NomePonto, NotaPonto)]
pontos lista n = [(nome, nota) | (nome, nota, tipo) <- lista, nota >= n && tipo == "parque" || tipo == "museu"]