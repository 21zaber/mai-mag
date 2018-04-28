prior = [ 3, 3, 4, 4, 3, 3 ]

px = 0
py = 0
pa = 0

m = []

j = 0
while j < 6
	s = gets.chomp
    m = m + [s]
	for i in (0..8)
		if s[i] == '.'
			y = i
			if y > 4
				y = y - 2
			else
				if y > 1
					y = y -1
				end
			end
			
			a = prior[y] - j / 2
			if a > pa
				px = j
				py = i
				pa = a
			end
        end
	end
    j = j + 1
end

m[px][py] = "P"

for i in (0..5)
    print m[i], "\n"
end


