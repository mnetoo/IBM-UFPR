module Lista4 where

leNome :: (String, String, Char) -> String
leNome (nome, _, _) = nome

leGraduacao :: (String, String, Char) -> String
leGraduacao (_, graduacao, _) = graduacao

leGenero :: (String, String, Char) -> Char
leGenero (_, _, genero) = genero

-- -----------------------------------------------------------------

base :: Int -> (String, String, Char)
base x
    |x == 1 = ("joao", "mestre", 'm')
    |x == 2 = ("jonas", "doutor", 'm')
    |x == 3 = ("joice", "mestre", 'f')
    |x == 4 = ("janete", "doutor", 'f')
    |x == 5 = ("jose", "mestre", 'm')
    |otherwise = ("ninguem", "nada", 'x')

contMestre :: Int -> Int
contMestre x
    | x < 1 = 0
    | leGraduacao (base x) == "mestre" = 1 + contMestre (x - 1)
    | otherwise = contMestre(x - 1)

contDoutor :: Int -> Int
contDoutor x
    | x < 1 = 0
    | leGraduacao (base x) == "doutor" = 1 + contDoutor (x - 1)
    | otherwise = contDoutor(x - 1)

contMD :: Int -> String -> Int
contMD x graduacao = 
    if(x < 1) then 0
    else if(graduacao == "doutor") then 
        if(leGraduacao (base x) == "doutor") then 1 + contMD (x - 1) graduacao
        else contMD (x - 1) graduacao
    else 
        if(leGraduacao (base x) == "mestre") then 1 + contMD (x - 1) graduacao
        else contMD (x - 1) graduacao

cont :: Int -> String -> Char -> Int
cont x graduacao genero
    | x < 1 = 0
    | leGraduacao (base x) == graduacao && leGenero (base x) == genero = 1 + cont (x - 1) graduacao genero
    | otherwise = cont (x - 1) graduacao genero

-- -----------------------------------------------------------------

type NomePesq = String
type GraduacaoPesq = String
type GeneroPesq = Char
type Pesquisador = (NomePesq, GraduacaoPesq, GeneroPesq)
type Pesquisadores = [Pesquisador]

listaPesquisadores :: Int -> Pesquisadores
listaPesquisadores x
    | x < 1 = []
    | x <= 5 = base x : listaPesquisadores (x - 1)
    | otherwise = listaPesquisadores (x - 1)

listaDoutores :: Pesquisadores -> [NomePesq]
listaDoutores [] = []
listaDoutores lista = [nome | (nome, graduacao, genero) <- lista, graduacao == "doutor"]

listaMestre :: Pesquisadores -> [NomePesq]
listaMestre [] = []
listaMestre lista = [nome | (nome, graduacao, genero) <- lista, graduacao == "mestre"]

-- -----------------------------------------------------------------

addSr :: String -> String
addSr nome = "Sr. " ++ nome

addSra :: String -> String
addSra nome = "Sra. " ++ nome

addSrta :: String -> String
addSrta nome = "Srta. " ++ nome

addTratamento :: (String -> String) -> [String] -> [String]
addTratamento _ [] = []
addTratamento f (h:t) = (f h) : (addTratamento f t)

-- -----------------------------------------------------------------

positivo :: Int -> Bool
positivo x
    | x > 0 = True
    | otherwise = False

negativo :: Int -> Bool
negativo x
    | x < 0 = True
    | otherwise = False

zero :: Int -> Bool
zero x
    | x == 0 = True
    | otherwise = False

verificaNumero :: (Int -> Bool) -> [Int] -> [Int]
verificaNumero _ [] = []
verificaNumero f (h:t)
    | (f h) == True = h : (verificaNumero f t)
    | otherwise = verificaNumero f t

-- -----------------------------------------------------------------