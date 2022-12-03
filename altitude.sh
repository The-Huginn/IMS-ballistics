awk 'BEGIN{a = 0}{if ($2 ~/^[0-9]+/ && $2 > a) a = $2}END{print a}' simulation.dat
