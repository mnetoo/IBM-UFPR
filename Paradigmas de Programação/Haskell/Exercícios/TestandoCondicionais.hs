module TestantoCondicionais where

-- -------------------------------------------------------------------------------------

-- Usando Guarda
verificaIdade_G :: Int -> String
verificaIdade_G idade
    | idade >= 18 = "Maior de Idade"
    | otherwise = "Menor de Idade"

-- Usando if-then-else
verificaIdade_I :: Int -> String
verificaIdade_I idade = 
    if(idade >= 18) then "Maior de Idade" 
    else "Menor de Idade"

-- -------------------------------------------------------------------------------------

-- Usando Guarda
verificaNumero_G :: Int -> String
verificaNumero_G numero
    | numero > 0 = "Positivo"
    | numero == 0 = "Igual a Zero"
    | otherwise = "Negativo"

-- Usando if-then-else
verificaNumero_I :: Int -> String
verificaNumero_I numero = 
    if(numero > 0) then "Positivo"
    else if(numero == 0) then "Igual a Zero"
    else "Negativo"

-- -------------------------------------------------------------------------------------

-- Usando Guarda
verificaBissexto_G :: Int -> Bool
verificaBissexto_G ano
    | mod ano 400 == 0 = True
    | (mod ano 4 == 0) && (mod ano 100 /= 0) = True
    | otherwise = False

-- Usando Guarda com where
verificaBissexto_GW :: Int -> Bool
verificaBissexto_GW ano
    | por400 == 0 = True
    | (por4 == 0) && (por100 /= 0) = True
    | otherwise = False
    where
        por400 = mod ano 400
        por4 = mod ano 4
        por100 = mod ano 100

-- Usando if-then-else
verificaBissexto_I :: Int -> Bool
verificaBissexto_I ano =
    if(mod ano 400 == 0) then True
    else if(mod ano 4 == 0 && mod ano 100 /= 0) then True
    else False

-- Usando if-then-else com where
verificaBissexto_IW :: Int -> Bool
verificaBissexto_IW ano =
    if(por400 == 0) then True
    else if(por4 == 0 && por100 /= 0) then True
    else False
    where
        por400 = mod ano 400
        por4 = mod ano 4
        por100 = mod ano 100

-- -------------------------------------------------------------------------------------