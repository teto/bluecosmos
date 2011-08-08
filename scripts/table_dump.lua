
function table.dump(t)
	
	--t.concat()
	for key,val in pairs(t) do
		--["..val.."]
		print("Key ["..key.."] of type "..type(val).." with value ");
	end
end


    function serialize (o)
      if type(o) == "number" then
        io.write(o)
      elseif type(o) == "string" then
        io.write(string.format("%q", o))
      elseif type(o) == "table" then
        io.write("{\n")
        for k,v in pairs(o) do
          io.write("  ", k, " = ")
          serialize(v)
          io.write(",\n")
        end
        io.write("}\n")
      else
        error("cannot serialize a " .. type(o))
      end
    end