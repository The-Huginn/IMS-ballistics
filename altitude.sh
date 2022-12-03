gawk 'BEGIN{a = 0}{if ($2 ~/^[0-9]+/ && strtonum($2) > strtonum(a)) a = $2}END{print a}' simulation.dat
