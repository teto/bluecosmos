function configureYF19Player()

--print('hello world');
    Transformer.getMode(Transformer.yf19_Fighter)
        :setupSpeeds(0.4 , --lateral speed
                     2   ,    --fwd
                     0.4 , --default fwd
                     0.9 , --backward
                     2 , --rolling
                     0.2) --yaw
        :setRange(3)
        :setAngleBounds(0,40)
        :setCameraRecul(0,20,-50);


    Transformer.getMode(Transformer.yf19_Gerwalk)
        :setupSpeeds(0.5 , --lateral speed
                     1.5   ,    --fwd
                     0.2 , --default fwd
                     1 , --backward
                     0.3 , --rolling
                     0.2) --yaw
        :setRange(3)
        :setAngleBounds(40,0)
        :setCameraRecul(0,10,-30);

    Transformer.getMode(Transformer.yf19_Battloid)
        :setupSpeeds(0.6 , --lateral speed
                     1.2 ,    --fwd
                     0. , --default fwd
                     1.2 , --backward
                     0.3 , --rolling
                     0.8) --yaw
        :setRange(3)
        :setAngleBounds(80,0)
        :setCameraRecul(0,20,-20);

end
