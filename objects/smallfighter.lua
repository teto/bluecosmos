
--math.sin
--math.min

function think (self)

	--self.age =
	dmg = self.obj:getDamage();
	--print("LUA: damage"..dmg);
	if(self.obj:getDamage() > 0) then
        print("LUA: tuee !\n");
        --Level:removeEnemyBattery(self.obj);
        return true;
    end
	self.z = self.z - 0.04;
	self.obj:pos(self.x,self.y,self.z)
    self.obj:update(Engine:getElapsedTime());
	--print ("update a smallfighter unit");
	--if(self.obj:destroyed()) then return true; end;
end


return think;
