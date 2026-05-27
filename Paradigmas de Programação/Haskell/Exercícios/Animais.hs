module Animais where

-- Uma clínica veterinária armazena seus pacientes como tuplas (String, String, Int, Char), 
-- representando (nomeDoAnimal, especie, idade, porte), onde porte pode ser 'P' (pequeno), 'M' (médio) ou 'G' (grande).

-- a) Utilize type para criar os apelidos NomeAnimal, Especie, Idade, Porte e Animal.
type NomeAnimal = String
type EspecieAnimal = String
type IdadeAnimal = Int
type PorteAnimal = Char
type Animal = (NomeAnimal, EspecieAnimal, IdadeAnimal, PorteAnimal)

-- b) Escreva uma função recursiva contarPorEspecie :: Especie -> [Animal] -> Int que conte quantos animais de uma 
-- determinada espécie estão cadastrados.
contaPorEspecie :: EspecieAnimal -> [Animal] -> Int
contaPorEspecie _ [] = 0
contaPorEspecie  esp ((_, especie, _, _):t)
    | especie == esp = 1 + contaPorEspecie esp t
    | otherwise = contaPorEspecie esp t

-- c) Escreva uma função recursiva maisVelho :: [Animal] -> NomeAnimal que retorne o nome do animal mais velho da 
-- lista. Assuma que a lista nunca é vazia e que não há empate.
obterIdade :: NomeAnimal -> [Animal] -> IdadeAnimal
obterIdade _ [] = 0
obterIdade nomeProcurado ((nome, _, idade, _):t)
    | nome == nomeProcurado = idade
    | otherwise = obterIdade nomeProcurado t

maisVelho :: [Animal] -> NomeAnimal
maisVelho [(nome, _, _, _)] = nome
maisVelho ((nome, _, idade, _):t)
    | idade > idadeMaisVelhoResto = nome
    | otherwise = nomeMaisVelhoResto
    where
        nomeMaisVelhoResto = maisVelho t
        idadeMaisVelhoResto = obterIdade nomeMaisVelhoResto t

-- d) Escreva uma função recursiva filtrarPorteEspecie :: Porte -> Especie -> [Animal] -> [Animal] que retorne apenas 
-- os animais que satisfaçam ambas as condições: porte e espécie informados.
porPorte :: Animal -> PorteAnimal -> Bool
porPorte (_, _, _, porte) p = porte == p

porEspecie :: Animal -> EspecieAnimal -> Bool
porEspecie (_, especie, _, _) e = especie == e

filtrarPorteEspecie :: (Animal -> PorteAnimal -> Bool) -> PorteAnimal -> (Animal -> EspecieAnimal -> Bool) 
                                        -> EspecieAnimal -> [Animal] -> [Animal]
filtrarPorteEspecie _ _ _ _ [] = []
filtrarPorteEspecie fPorte p fEspecie e (h:t)
    | fPorte h p && fEspecie h e = h : filtrarPorteEspecie fPorte p fEspecie e t
    | otherwise = filtrarPorteEspecie fPorte p fEspecie e t

filtrarPorteEspecie2 :: PorteAnimal -> EspecieAnimal -> [Animal] -> [Animal]
filtrarPorteEspecie2 p e animais= [(nome, especie, idade, porte) | (nome, especie, idade, porte) <- animais, 
                                    especie == e && porte == p]

-- e) Escreva uma função recursiva de alta ordem mapearIdade :: (Idade -> Idade) -> [Animal] -> [Animal] que aplique uma 
-- transformação à idade de todos os animais da lista, retornando a lista atualizada.
envelhecer :: IdadeAnimal -> IdadeAnimal
envelhecer idade = idade + 10

mapearIdade :: (IdadeAnimal -> IdadeAnimal) -> [Animal] -> [Animal]
mapearIdade _ [] = []
mapearIdade env ((nome, especie, idade, porte):t) = (nome, especie, env idade, porte) : mapearIdade env t 