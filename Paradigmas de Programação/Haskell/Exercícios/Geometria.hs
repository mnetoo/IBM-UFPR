module Geometria where

-- Exercicio 4

-- a) Uma função areaCirculo :: Float -> Float que calcule a área de um círculo dado o raio. (use pi = 3.14)
areaCirculo :: Float -> Float
areaCirculo x
    | x == 0.0 = 0
    | otherwise = x * 3.14

-- b) Uma função areaRetangulo :: Float -> Float -> Float que calcule a área de um retângulo dados largura e altura.
areaRetangulo :: Float -> Float -> Float
areaRetangulo 0 _ = 0.0
areaRetangulo _ 0 = 0.0
areaRetangulo x y = x * y

-- c) Uma função areaQuadrado :: Float -> Float que calcule a área de um quadrado dado o lado.
areaQuadrado :: Float -> Float
areaQuadrado 0.0 = 0.0
areaQuadrado x = x * x

-- d) Uma função recursiva de alta ordem somarAreas :: [Float] -> (Float -> Float) -> Float que receba uma lista de medidas 
-- e uma função de área (apenas para funções de um parâmetro), retornando a soma de todas as áreas calculadas.
somarAreas :: [Float] -> (Float -> Float) -> Float
somarAreas [] _ = 0.0
somarAreas (h:t) f = (f h) + somarAreas t f