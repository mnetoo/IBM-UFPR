module Matematica where

ehMultiplo3 :: Int -> Bool
ehMultiplo3 x = 
    if(mod x 3 == 0) then True
    else False

ehMultiplo5 :: Int -> Bool
ehMultiplo5 x = 
    if(mod x 5 == 0) then True
    else False

filtrarMultiplos :: [Int] -> (Int -> Bool) -> [Int]
filtrarMultiplos [] _ = []
filtrarMultiplos (h:t) f =
    if(f h) then h : filtrarMultiplos t f
    else filtrarMultiplos t f