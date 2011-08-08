--[[levelinfo = {
width = 200,
height = 200,
name = "test"
}
]]--


local refs = {}


for i=1,1464 do refs[i] = {} end

refs[6][1] = 0
refs[6][2] = 0
refs[6][3] = 0

--enemy wave
refs[2]["activator"] = function() return onReach(0.5) end;
refs[2]["activate"]  = function()
                                    spawn(-10,0,50,"models/spacefighter.obj");
                                    spawn(10,0,50,"models/spacefighter.obj");
                                    spawn(5,0,50,"models/spacefighter.obj");
                                    end;
--refs[2]["times"]    = 3;
--refs[2]["interval"]  = 1000; -- ms*


refs[3]["activator"] = function() return onReach(0.2) end;
refs[3]["activate"]  = function()
                            --Engine:startDialog(dofile("scripts/dialog.lua"))
                            --dofile("scripts/dialog.lua")
                            actor1 = Level:addActor("Eldaric","images/portraits/eldaric.png");
                            actor2 = Level:addActor("Logalmier","images/portraits/logalmier.png");

                            --,"sounds/bgm.mp3"actor1,
                            local speech = CLevelManager.createSpeech("Hi buddy welcome in the tutorial ! Press W to go on.", "sounds/bgm.mp3");

                            print("calling Show message");

                            MainState:showMessage(actor1,speech);


                            local ret = MainState:getPlayerReply();
                            print ("reply ",ret);
                        end;
--refs[2]["times"]    = 3;


refs[4]["activator"] = function() return onReach(10) end;
refs[4]["activate"]  = function() return spawn(0,0,20,"models/spacefighter.obj"); end;


refs[4]["activator"] = function() return onReach(5) end;
refs[4]["activate"]  = function() return spawn(3,0,20,"models/spacefighter.obj"); end;


refs[5]["activate"]  =  function()
                            --local sound = CSound("sounds/bgm.mp3");
                            --sound:Play();
                        end;

--trigger.type          = starDialog/spawn/perso
--refs[2]["battery.file"] = "batteries/bullet.xml";
--refs[2]["battery.id"] = "dummy";
--refs[2]["game.enemytype"] = "smallfighter"
--refs[2]["battery.think"] = dofile("scripts/smallfighter.lua");


refs[1][1] = refs[2]
--[[refs[1][2] = refs[3]--dialog

refs[1][3] = refs[4]
refs[1][3] = refs[5]


refs[1][4] = refs[23]
refs[1][5] = refs[30]
refs[1][6] = refs[37]
refs[1][7] = refs[44]
refs[1][8] = refs[51]
refs[1][9] = refs[58]
refs[1][10] = refs[65]
refs[1][11] = refs[72]
refs[1][12] = refs[79]
refs[1][13] = refs[86]
refs[1][14] = refs[93]
refs[1][15] = refs[100]
refs[1][16] = refs[107]
refs[1][17] = refs[114]
refs[1][18] = refs[121]
refs[1][19] = refs[128]
refs[1][20] = refs[135]
refs[1][21] = refs[142]
refs[1][22] = refs[149]
refs[1][23] = refs[156]
refs[1][24] = refs[163]
refs[1][25] = refs[170]
refs[1][26] = refs[177]
refs[1][27] = refs[184]
refs[1][28] = refs[191]
refs[1][29] = refs[198]
refs[1][30] = refs[205]
refs[1][31] = refs[212]
refs[1][32] = refs[219]
refs[1][33] = refs[226]
refs[1][34] = refs[233]
refs[1][35] = refs[240]
refs[1][36] = refs[247]
refs[1][37] = refs[254]
refs[1][38] = refs[261]
refs[1][39] = refs[268]
refs[1][40] = refs[275]
refs[1][41] = refs[282]
refs[1][42] = refs[289]
refs[1][43] = refs[296]
refs[1][44] = refs[303]
refs[1][45] = refs[310]
refs[1][46] = refs[317]
refs[1][47] = refs[324]
refs[1][48] = refs[331]
refs[1][49] = refs[338]
refs[1][50] = refs[345]
refs[1][51] = refs[352]
refs[1][52] = refs[359]
refs[1][53] = refs[366]
refs[1][54] = refs[373]
refs[1][55] = refs[380]
refs[1][56] = refs[387]
refs[1][57] = refs[394]
refs[1][58] = refs[401]
refs[1][59] = refs[408]
refs[1][60] = refs[415]
refs[1][61] = refs[422]
refs[1][62] = refs[429]
refs[1][63] = refs[436]
refs[1][64] = refs[443]
refs[1][65] = refs[450]
refs[1][66] = refs[457]
refs[1][67] = refs[464]
refs[1][68] = refs[471]
refs[1][69] = refs[478]
refs[1][70] = refs[485]
refs[1][71] = refs[492]
refs[1][72] = refs[499]
refs[1][73] = refs[506]
refs[1][74] = refs[513]
refs[1][75] = refs[520]
refs[1][76] = refs[527]
refs[1][77] = refs[534]
refs[1][78] = refs[541]
refs[1][79] = refs[548]
refs[1][80] = refs[555]
refs[1][81] = refs[562]
refs[1][82] = refs[569]
refs[1][83] = refs[576]
refs[1][84] = refs[583]
refs[1][85] = refs[590]
refs[1][86] = refs[597]
refs[1][87] = refs[604]
refs[1][88] = refs[611]
refs[1][89] = refs[618]
refs[1][90] = refs[625]
refs[1][91] = refs[632]
refs[1][92] = refs[639]
refs[1][93] = refs[646]
refs[1][94] = refs[653]
refs[1][95] = refs[660]
refs[1][96] = refs[667]
refs[1][97] = refs[674]
refs[1][98] = refs[681]
refs[1][99] = refs[688]
refs[1][100] = refs[695]
refs[1][101] = refs[702]
refs[1][102] = refs[709]
refs[1][103] = refs[716]
refs[1][104] = refs[723]
refs[1][105] = refs[730]
refs[1][106] = refs[737]
refs[1][107] = refs[744]
refs[1][108] = refs[751]
refs[1][109] = refs[758]
refs[1][110] = refs[765]
refs[1][111] = refs[772]
refs[1][112] = refs[779]

refs[1][113] = refs[786]
refs[1][114] = refs[793]
refs[1][115] = refs[800]
refs[1][116] = refs[807]
refs[1][117] = refs[814]
refs[1][118] = refs[821]
refs[1][119] = refs[828]
refs[1][120] = refs[835]
refs[1][121] = refs[842]
refs[1][122] = refs[849]
refs[1][123] = refs[856]
refs[1][124] = refs[863]
refs[1][125] = refs[870]
refs[1][126] = refs[877]
refs[1][127] = refs[884]
refs[1][128] = refs[891]
refs[1][129] = refs[898]
refs[1][130] = refs[905]
refs[1][131] = refs[912]
refs[1][132] = refs[919]
refs[1][133] = refs[926]
refs[1][134] = refs[933]
refs[1][135] = refs[940]
refs[1][136] = refs[947]
refs[1][137] = refs[954]
refs[1][138] = refs[961]
refs[1][139] = refs[968]
refs[1][140] = refs[975]
refs[1][141] = refs[982]
refs[1][142] = refs[989]
refs[1][143] = refs[996]
refs[1][144] = refs[1003]
refs[1][145] = refs[1010]
refs[1][146] = refs[1017]
refs[1][147] = refs[1024]
refs[1][148] = refs[1031]
refs[1][149] = refs[1038]
refs[1][150] = refs[1045]
refs[1][151] = refs[1052]
refs[1][152] = refs[1059]
refs[1][153] = refs[1066]
refs[1][154] = refs[1073]
refs[1][155] = refs[1080]
refs[1][156] = refs[1087]
refs[1][157] = refs[1094]
refs[1][158] = refs[1101]
refs[1][159] = refs[1108]
refs[1][160] = refs[1115]
refs[1][161] = refs[1122]
refs[1][162] = refs[1129]
refs[1][163] = refs[1136]
refs[1][164] = refs[1143]
refs[1][165] = refs[1150]
refs[1][166] = refs[1157]
refs[1][167] = refs[1164]
refs[1][168] = refs[1171]
refs[1][169] = refs[1178]
refs[1][170] = refs[1185]
refs[1][171] = refs[1192]
refs[1][172] = refs[1199]
refs[1][173] = refs[1206]
refs[1][174] = refs[1213]
refs[1][175] = refs[1220]
refs[1][176] = refs[1227]
refs[1][177] = refs[1234]
refs[1][178] = refs[1241]
refs[1][179] = refs[1248]
refs[1][180] = refs[1255]
refs[1][181] = refs[1262]
refs[1][182] = refs[1269]
refs[1][183] = refs[1276]
refs[1][184] = refs[1283]
refs[1][185] = refs[1290]
refs[1][186] = refs[1297]
refs[1][187] = refs[1304]
refs[1][188] = refs[1311]
refs[1][189] = refs[1318]
refs[1][190] = refs[1325]
refs[1][191] = refs[1332]
refs[1][192] = refs[1339]
refs[1][193] = refs[1346]
refs[1][194] = refs[1353]
refs[1][195] = refs[1360]
refs[1][196] = refs[1367]
refs[1][197] = refs[1374]
refs[1][198] = refs[1381]
refs[1][199] = refs[1388]
refs[1][200] = refs[1395]
refs[1][201] = refs[1402]
refs[1][202] = refs[1409]
refs[1][203] = refs[1416]
refs[1][204] = refs[1423]
refs[1][205] = refs[1430]
refs[1][206] = refs[1437]
refs[1][207] = refs[1444]
refs[1][208] = refs[1451]
refs[1][209] = refs[1458]
--]]

return refs[1];
