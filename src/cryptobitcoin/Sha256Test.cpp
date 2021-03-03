/*
 * A runnable main program that tests the functionality of class Sha256.
 *
 * Bitcoin cryptography library
 * Copyright (c) Project Nayuki
 *
 * https://www.nayuki.io/page/bitcoin-cryptography-library
 * https://github.com/nayuki/Bitcoin-Cryptography-Library
 */

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "Sha256.hpp"
#include "Sha256Hash.hpp"
#include "TestHelper.hpp"

/*---- Structures ----*/

struct TestCase {
  bool matches;
  const char *expectedHash;  // In byte-reversed order
  Bytes message;
};

// Global variables
static int numTestCases = 0;

/*---- Test suite ----*/

// Remember that all 256-bit hash strings are byte-reversed as per the Bitcoin
// convention.

static void testSingleHash() {
  // Single SHA-256 hash
  const vector<TestCase> singleCases{
      // Standard test vectors
      {true, "55B852781B9995A44C939B64E441AE2724B96F99C8F4FB9A141CFC9842C4B0E3",
       asciiBytes("")},
      {true, "BB48EEAF857780B9724E7C14F8EF86A74DDC239AB331C2FACABD1BCA128197CA",
       asciiBytes("a")},
      {true, "AD1500F261FF10B49C7A1796A36103B02322AE5DDE404141EACF018FBF1678BA",
       asciiBytes("abc")},
      {true, "50B63C393D41A1A3EFC4FB48339E505BAD0C55E1B4B5EAEB4EE123CF556F84F7",
       asciiBytes("message digest")},
      {true, "738BF1DAF232D89E8DFC51CF1862315E52C9667C44D1FA1E2FAED693DF80C471",
       asciiBytes("abcdefghijklmnopqrstuvwxyz")},
      {true, "C106DB19D4EDECF66721FF6459E43CA339603E0C9326C0E5B83806D2616A8D24",
       asciiBytes("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq")},
      // Mismatches caused by slight perturbations
      {false,
       "55B852781B9995A44C939B64E441AE2724B96F79C8F4FB9A141CFC9842C4B0E3",
       asciiBytes("")},
      {false,
       "BB48EEAF857780B9724E7C14F8EF86A74DDC239AB331C2FACABD1BCA128197CA",
       asciiBytes("b")},
      // Random printable-ASCII test vectors of increasing length
      {true, "12519F99DE14034A3AA90D64469E307CAE43C5D0D0182C21F92032E922E07339",
       asciiBytes("-")},
      {true, "58F4584D67F9FFCEDB92F76E386E44D5ECD97AF3EEE0D57712D0B8893831F5CD",
       asciiBytes("O4")},
      {true, "C69B69FD9C933F0F6FA6A41FA2F9E0830E88F27126230365C2446C9CB1C236C5",
       asciiBytes("Qz5")},
      {true, "109DA8D29F0D36355D618EF7F05170C5FF69E32B0F7A8F6EFA2714DD1F1A7151",
       asciiBytes("Y$h/")},
      {true, "82430AFD2A2EF8F7167A75A4A2DFCAB7573EA754E870DE8C71A65520F78B9A66",
       asciiBytes("p(kaX")},
      {true, "05ABEEFF1D8BD80CA018415E262DCC2E5CEDD54109A11EADC6F6E7D4F48F120D",
       asciiBytes("\"i?#/S")},
      {true, "CCABDDBD2F828FC5BFA15651A60FDC22E8C6EC1070ACC9A32A1DD7FFFBB5C68A",
       asciiBytes(";C7zRLL")},
      {true, "74A83C377597B3F45D6698A06D1BA3A3960252469C5CC20FD34CBA2F2EE13BE9",
       asciiBytes("1eZ0a*(u")},
      {true, "21C2DC51434674770786628E9EC59E2341351F9193A14B9661A8F8A5B25D9079",
       asciiBytes("4?P[@+J5D")},
      {true, "C61169091B4D50105B91A89B73768B994373AB655F8565F10A3B6974DFC1EDB0",
       asciiBytes("G]ipN8[69O")},
      {true, "C02CC8860E8562CE09BDDE7A9F091D364D6B8D6410915B0C119C4D7F8DA00084",
       asciiBytes("jWhXp?l)0Ws")},
      {true, "EFBDF767E0D5D11F73A97B5A554A142511649C7E78197DDC40E5DC1F55C9BCF6",
       asciiBytes("U!0WFh~5J=,4")},
      {true, "FBA0B40D9264D56EC7A4C302FEE71702D9A2CDC7D2F241F77CD2A7E496B279EC",
       asciiBytes("m67V.]u6]%!`N")},
      {true, "C9D8CDD32502F9123F0FC9D932B16F9113D633FABE7387C52A52689D1C3BE7A4",
       asciiBytes("TbS'R]jANh?pM$")},
      {true, "D14003A6CB0039E91F1D8935648E9837BE927FCF06ACDA64EAC3A3D16ED5FD09",
       asciiBytes("KbGSWuU%6FNq xR")},
      {true, "B6D9677D4CFC14EC96F964810F1D0F22638FDAB4AEE0B0E681824792878B5370",
       asciiBytes("!lqe]~UJsqb)Li5t")},
      {true, "63A676D1304ADEB737450A00153E44A6B144E4BBC19F0F22BAE97AD4B1811592",
       asciiBytes("L^O%CcsTCgH%q!Ct*")},
      {true, "A55870E9A6FBB684D21602407033AD4074EF215F86ADC48424A69F56C3918E26",
       asciiBytes("O!Vx(?<Gy: j=EA`^%")},
      {true, "99DEAACD61A2894BBFCC101E02DDD811E693617B40057B2CA002C959872FF262",
       asciiBytes("z0L|?AG$>3L<)xP6I%\"")},
      {true, "C73E9BD7719DC2AD90B2069325C5626E039FAA8DFDFB5E58D2A033EFCF692A03",
       asciiBytes("G(UOs.5lvi(xR;+OU\"/{")},
      {true, "6F0188BE07910E8657065B7189EF5D6DBD8C7D680F71BC0BA6235559E64D957B",
       asciiBytes("9\"/m921Iwl[.<)toSRk5g")},
      {true, "1E3D608223C332142F0DEE8CB68183B83BD59BF12D2B5BE332F918794F6CC9A8",
       asciiBytes("zYoz{w@8],,9@q6n?!m/_ ")},
      {true, "3F2888E93A10EBD7DF7AF407F9EB2CE33697066B17B20298A4BD0C0A8600ECFB",
       asciiBytes("*Kn|.@jG{(mxNO{L!gLZzr?")},
      {true, "A6DBD41504F785E88B5682746EFA97C4894A2D1C13980013B80103AAAE1293B6",
       asciiBytes("hC9E2&bbEg4hO%2\"<|Q^\"`&r")},
      {true, "8FD5CDF9073F314889B58113557ED822CCF0803FAAE3409CE036FD7D74F49CA0",
       asciiBytes("<N<?~Wx?jqh+[\"63(:'82Ch5O")},
      {true, "D3180B726A47F8E4EC466A79F3C5B4EA2160496276E0027E2660A1980480280E",
       asciiBytes("H@0{\\JEBym}/T0H#gz:2f_w|aP")},
      {true, "8F25F061C2E0F2A7F0ABD8A16017168A6BE5271DFBE24987DF830C99053C8E3A",
       asciiBytes("{Zw4fe6Eieg#+}H%D[Cb(_]0=0M")},
      {true, "F9225FAAF43D338F93A2D8E932A1E423C270AA83E221ED97F28C0E5A0D166EBC",
       asciiBytes("hyLGQh3_K|9pgqxg{X?|CYY_|h,$")},
      {true, "9F7FE14AE87E3BCF46D482665C062378E32CB42C410A5F3361DDEC11E09D8105",
       asciiBytes("GT;\"&%s{ae7h,#6*ea1\\~87c7{=:O")},
      {true, "66CEC32F20B76EDC8AF4F83629EF3A7AFA0F7FEC00C7E889B2D4AEAFED90CB3A",
       asciiBytes("0GhILn%$~D(TuHA\"#QK`9F=y?t6mbm")},
      {true, "62A4C56BC2C2EA5821C323431B4A4EABF309896285505C68016CB6434731D037",
       asciiBytes("hSbJE 8gA&_Jz]B&'_b3R;m*!N}dlE]")},
      {true, "CEDF17B4AD93419B7B7DB695B72B0D4A55D5CFE89241E699898C32CE13670E18",
       asciiBytes("EgM%B~rQv2~EkE7+ 3`MBM6j5Zp>*TwO")},
      {true, "CED452EE980D313C1C483CCB95153B27606C1FD4060D015D99E52EAA8CFC76E5",
       asciiBytes("orf=wMzQ/|V$Q;ZnYi*)2VpL<\",dB|/s#")},
      {true, "3BE75C942520147C75E3C01FC6A03DB9CDB3EFDA8F783EF769C6E992F82534F8",
       asciiBytes("k<d}Uy:+%JYHr4Mv1lYhpIUUS?=-dwW45!")},
      {true, "C9A6E47A69A0CBC1B5B129209D9187959DD0F8D5633DB27080486057FD684063",
       asciiBytes("c-EB00tL'=TQ@i$b6s@_aI&fICA80TUI,BQ")},
      {true, "84D31A55A61CB4B9E9EBB5E4F851A58E4C28CEC34B39E48E7C27229C82AE5567",
       asciiBytes("pBC3Zeck.|Yi571V`g(SJf=/R<)\"ux;z:XtG")},
      {true, "5F254A802579FAC2255123E69CB711270ACEA1EB6E5C2CAE0F014E0361EBD8CC",
       asciiBytes("Ai5[N[s v?CL^$H92q6z=^\"G?}e$8cn<qn5gO")},
      {true, "A84EDBE255C7ABB69C66961AEF61E20721BB974BB2B6CB3D7BE33ADB0A5BC9EE",
       asciiBytes("d27eE1x *|3,H`8mtu*!DmX~wO}*:vW,k~d}'y")},
      {true, "1AFA1DD2965650D03EF935A1A0617794BADDFFFEDF2BD26CD6A75816492C5E8B",
       asciiBytes("*Y1HvEQ^jB131g?Da~g$O,E|rc7AVR$H9laT*7d")},
      {true, "69DD41EF45671445E0AF3D1389152CC681DE49BDBC593F96B50C879507AD3AD5",
       asciiBytes("2/6<-xS4E)1:p<~!,.^.>AX9AyaAVbP3/k>MU88A")},
      {true, "B92DACB6A360DE574BEBB8E22315D95D9D79AEA5D895F8A6B475CF8979E7BB14",
       asciiBytes("%,-v7y@\\T+`^=ais olL8\"7;]kUc{.p'$*iRyYyEt")},
      {true, "E3C5C024E5723D11CC360F368AD0606432F6FD5F469805FD2C4DF81E627E9B3F",
       asciiBytes("HGqueCu(AZV:;R+h eE5*VX``jRn1>Y1>PVO.;ai7K")},
      {true, "1B9B11F5268027A26E84402BE0E18F54C44D262C61238DD376BD7B093E64E236",
       asciiBytes("+f5d0;l;~/YPaU{T#,81IgtLzPNbR}@p)8S O>*rFOm")},
      {true, "3B07EC8C0419A362A8FD7E02C450BF67B1E3F1DCCEF77DD9F20751936FD64917",
       asciiBytes("H$T-S.9H(nI~b5{}a3,_0f4Bk#zEh5D3Bhii`@qZ*X*)")},
      {true, "75D294BACF2383C0A1B034F5A4AAAFDD44A92FC0F71F53CD4F6ED9478D2E4E02",
       asciiBytes("l:EE?=fruAeU\\%jl~1<N_lH6ibQUx*0D\\k\"#`cO\"(xTI_")},
      {true, "8DB849243E2DB44B94CDD59C7A8E6E76D4F7324906CE815F2193BDB5098AECE0",
       asciiBytes("l S$@Ay'*qj#6l_YU98pS#zZb,p}MWb-&QD}ZfK6z~nR0@")},
      {true, "21F4D945725352AAA2B4C20254A9B2C68FA9EAE5461D3C6B773B745956457292",
       asciiBytes("Be*]CTIac|<4IsEbKL*;n=7nSU(HME=TL_F3&[3e=%Jmq}p")},
      {true, "029CEBFDCDFBAFC06390CADD54A93472E49211ADDE0D4DAB694B05BEDAD2813E",
       asciiBytes("V'(O@sMxFCK4G]fwG8PZ9&+MqI(})jN!hy8biBBN7XE*Fb}\"")},
      {true, "AC8F0A65812C01C9FE7FE69AA8DE31DA4683ED2EC1C74497643FEBFE4FC2B00F",
       asciiBytes("a6!-B}\\oT)W{G[YZJg9~5d?]2m`G;>>EqR-jl6g*h0a!;nfA=")},
      {true, "BAE22197CD51E5572D6A2780B8447844667FB35B1C2BC227DF93521F19F274B4",
       asciiBytes("\"sFIX?Jfm<g5o:oMvEwrffHWL$~qQ$d1ZyFIg/<0d5sBs[;k']")},
      {true, "8CE416FD0E24AD4B5D0AF0465FC45A52C0D7915026470008E79751ADD026058B",
       asciiBytes("[nT;M; G7\"^m~vREg((2FGD7DWR*'T(T%,b^7IRv5u/u?$BHKXh")},
      {true, "2D942B655215D095D6314F0515C9978056EDA583437580D28CFD405B5EF135C1",
       asciiBytes("[o#v&H$@?rgcD6.lZXmq: M9'})v1'##2wv>i:Z[dfQAAY~{tQ%)")},
      {true, "1E94945F3E6C18897A83ABB12AAE83CC3F29D73322A3A378A55E9DE9A8211208",
       asciiBytes("ii!.\\JgDf_{O\">~2OI.Jg6*YW(/I)f@+'!:^*yaa| WtH(th-ywrG")},
      {true, "845E6B3330590C34B21E536DE85E823F679E38ACD7B637EACE8D10F82AA588A1",
       asciiBytes("Qp~`wM$euEsC,j`RJ$MLX1QXqL'UsB`` q0X!^^w5;Y8CSM}Ueil%1")},
      {true, "F0075098AC874946F513D579ACC6FDB48B58A3B81BF47CF33011FAFB816F1D23",
       asciiBytes("hoqgC#/ .Hy*<iU&v{9(Bak5;EdG,]!/#=f9{Dok)SpU9*k<eqzv$0!")},
      {true, "138EBB0FD5D5FE1F718508EC392B8BEAAA80D2985ADCE0A3FE92159D4E599DFD",
       asciiBytes(
           "^+\"agIi)QL[-i1F<e$s>r!;A7dbK(Q cMk_oHi->K.Fm5PAFl\\._RB`>")},
      {true, "27A99B0EE8B70E4AF2C56795AAFF7F162BC4296EA9E14B3546885C19F3C0594F",
       asciiBytes("A8:'hG>=N)-~P}|BFo!6lH5TSyZ%pb',/'^Z1h'+8l40WDt^fY=a|^lfN")},
      {true, "42546CE891AFE745CBD4B7E1CB0D5B2E002D22C15702C859BDDB511D539034C4",
       asciiBytes(
           "myS$}g+g1CjA-o=?Je(>|sp/ld+[bnQoWsMMO.w6q][cp#fMH%g401+_)E")},
      {true, "62285BFB2057057A709F47B54F4BFD3D79BBE75605E19DF86DF6E56B65611539",
       asciiBytes(
           "UJIXtIC[qOKBF]t%gS\\6L73\"-}#Qh[V fhj>Tv8Q%32f|x0J!GNOUt4Q_0B")},
      {true, "8B2DF4395442B5625FA5887D9717A8B45181967414AC15AD9558702FBC9A84D1",
       asciiBytes(
           "o3cR\"wt8G7ebeMd8nG[{y8>%gOdWtAsqD?|2fACx-ld5R:^ILx(i?E!R?Dv>")},
      {true, "6DBF9E47237B086A98418FF5716A62945009A448ECE9043B278D162C6BD89A5E",
       asciiBytes(
           "9Bj_Uvj'.\\ fH92?W`SG,5lduHy19>P?hUuldA'4ymdCe.BJljDq$ '[c{P^Q")},
      {true, "53F99510CC9B28BED40BFB9CA97D3B0C8326DEE2E465526AE5025AEB5EE6FF56",
       asciiBytes(
           "%U9##V<M*!,~R@Ru1sL06:NL1Oflz&,qgHY^\\ABzl<EvksI?O9U3T=Dg&rOQ0;")},
      {true, "4F9B12A197CBA685C72DB9007CB22FB7D976C94488B6882141EA9F4783398118",
       asciiBytes("MPTd8\\7V#+@UziCgC1)6+c5#_))Hd'.T~'ym(f\\hYg'4V-eA<,6mkDFPP+"
                  "^,|Qx")},
      {true, "5A75C798D14A1F608303CC6C206FCF87ED460246E144813EFBD75660198DAC76",
       asciiBytes(
           "snIqsB*`CK}#ApzIf1M@wJ9q5XjY1/2-7_wc;uW_$})2KhUM@rZrTuxQF;<R<Tn$")},
      {true, "8F0B250D4096A8FABB5F982A4EE849ECD36BD249F1D0702F26B04C35BB32A5ED",
       asciiBytes(
           "1.;7Sk "
           "T\"^JP~]XwjR-FqLhYg0PHMT.r`^/X<Vd,N/Gii1GQk(G|}NyI3Y3(71$lg")},
      {true, "8CB2A98D578819EB6F8F148B033BEA781447F33FA2833D45926F6871D819649F",
       asciiBytes("+n/t}U?r>d0wZh*fi5p6W= "
                  "%B&>zR=bVE^az2U`Sp0B`yf/M$Z!*rMKvco|#x$uLA.")},
      {true, "DAD54AD1352771C5E967961AFF9E73BBF97BD02E070A311383536C838D458940",
       asciiBytes(")n%=%Qt#Z2mSw-5:'^-dYQP|abssfq>U}y4(f$%<B^?)&I44G\"[Ku\\d-T@"
                  "=\\c14orS@")},
      {true, "DE972098E745E2AA57988BAD8C419EB13A519CFFB4E594FB0D180B089CC0E3D1",
       asciiBytes("oj{dzNZz~fH6IR{@g-)v',KxJ/"
                  "_|zFm4H<SLSdC{yx%QFlX)<`6MKjykq@70YdNe#WtS")},
      {true, "56E5A4A44B2BAD66D5B3A6DE82F4A65D31C4F2F7DBC37903B94C49E451C2F7C2",
       asciiBytes("yvs,PKEiYma#+lM`L)!.\\`bx%lWm|7pdeM90e;mX)x9n5b "
                  "5>nfcQ*'/jNNU,Gu/kw^w6")},
      {true, "66B4661774B576F55813D33F2611136584597629AB9994DEE3BDCC7FB94253BD",
       asciiBytes("]/"
                  "N}Nsj:b^nmgtLh}))`S-iZE!DL5jfU1:5og|%Qv\\GYE_Q?[=H48b$#9w&"
                  "K2I!0YS2*G/")},
      {true, "3B49D3BE358DFAD8B2424A0C9473DD5CD0379585D61BEC192900E7C1E25E1227",
       asciiBytes("UZ5K^m+j "
                  "7K@p`nd~EW3V{,\\=Ceb](ANDRO}Sg8OSi!bv?|KEP,Ax=e|aC1<uMz<"
                  "\"CPkY>\"")},
      {true, "F1FF461E6A85EB561037FC77DF9FF414E14A00F037EF01F012D4870D6E10AACF",
       asciiBytes("]nTJ/"
                  "de2'*amCCD?4i,Ia-sgTPHY]%_eWo%~(ND0OLm2+tdBxA\\`]k'*,iA*uZ4|"
                  "^t5g,?UN")},
      {true, "F51908F5901B48B53D69F5753D15FCC21D30E52ECEFA5F3D6371ED6988F04406",
       asciiBytes("TDKQKs0>=G\\1?4@?.O8TTz0Z6m{o:Q%+Z#g{cFck*8K`ftnLB]Z%T,J.=~"
                  "i'ah}$E+H+$3`9r")},
      {true, "9E5B2B03920A11CBBAA863477DEA9445BC0BD0BB03F98234779A570A5ADD4D9B",
       asciiBytes(
           "U'tHcy*pHr2^[.k "
           "[Ah7Iv&{sEVwH2F#u1xmNGW2)/A>*cC&X7`3;VCkw[0;Zd[Z^0B*_[_mYx")},
      {true, "5AF612C1DFA1A843856B3BE7EB32A7FD6A5F5259EBBBF747F8B853BF0E73C271",
       asciiBytes(">;1!4wFLCeqBPaznHY}DF}P2v80.6:'#1eUL1<Z\"GD$X.B^CxRrBP?E96,"
                  "A@.gxfK}O)2Vc\"87V")},
      {true, "808B7845B099932F258213339F2EDDBA791852FDB5315A982FEB9A14E5FDAB86",
       asciiBytes("9JO_]J~ xAgG;NfOZVp6Z)Qw#'vxcau2(HOw]@YK+NQ$}D806 "
                  "$Q#b^n/z?]7%1id2-N52u)XOs*")},
      {true, "61BC52B41AFDE4E2CA2F198B2B4DED51B093F89554AABF453775545761BE0A37",
       asciiBytes(".ucfBmy!{jXL:Sa*W_`z'+-gWC`%\"24J.dDJ,E#(1[8q;MX?r`>&"
                  "wLKC6vA?HFpdEpC-L1\"HyCE[@")},
      {true, "AD5C13AFD04977B42737E34406DAA7CDE5F41F72FF0C094E790C8C9E99377C60",
       asciiBytes("Zd}x::j^~bj)n .;cbvRw&xi9.VA, "
                  "u\\a)axuWv,&=A$Kf5V9FKcJkJlsE\\h}Br72xWgsvN{5h\"Rz1")},
      {true, "DDBB79112192D0E9EFB810E993B8EDD0376359B6E09938358F40A1A7582EDB3F",
       asciiBytes("FLv&`nP5\\q&cLTAHE#J\\M9{QZ`ynI_nH%iIFd>35_5guv4Rb_gwTJRt_"
                  "fapg{k?_ABF{2<`tWaG1yip")},
      {true, "87A47BEBE1EA0E888432EDA50AF75187108F40A022D19700C1956D852520A83F",
       asciiBytes(",RZ0pEx4FKS(eG5#V>^^C=*9H't3fDK6DHj7]J'|EtMlw&;;unm*5BYbM'."
                  "n5!56L`Wz`m8gDz oHC:>")},
      {true, "05D9E0EC730A0B3E95E2293ADBCE329A58BF8B40FD1D3D521C02805C0C15A7E7",
       asciiBytes("IrK{1@)P,Ymvs.{'hpW0/<sD*o0}ETU?oH6AU)x18O?uBcLFHQ/"
                  "KAB\\oie[giYz)p9_!NFQ}5Bv-@I-d,")},
      {true, "289EBBFA6B725683007C1A51E7575A9284BAF99A74C8329FADDC759996D08608",
       asciiBytes("(M\"|IiWs\\Y\\}HvwZ57*-1^gUbpD54l`KO1)ci=Htwt.5!}wsf1;d-"
                  "o\\F[(tv(MC[G[<Pg/zaD9mOOpD[5a")},
      {true, "3052C44193D6B700270385575BC497C1A518A4A28542BFB5EE644F77DE70B327",
       asciiBytes("a/"
                  "cmlQ6cAMJgo-VvKtG@:$_I%W{9D,^36ghyGFy|B\"kC&#@+"
                  "pu\"P4meYaEub8,E!{G3akDp;BHv>E,!qILh")},
      {true, "E6EAB879FE3B40EDFBEE7D19E06DB1F87DCED1A4207210DDDC957B261A6D28C1",
       asciiBytes("3>qHD5>aN1Zv<KOj\"eAv~z|M!@2,'bRP? "
                  "vou6bJWP'T#X1d*X/Oxva[1:M4^bfD2:~;W<^Tg?6SzJZd 2/e")},
      {true, "95495148DA645DDE83869BCA4FDC6AD86CFEC3A3C792D299FCC2516AF6335727",
       asciiBytes("o26R9s1Ci9.>7&+au5$cLmm5#ymm[rnT6nL?CK_Ibo@/"
                  "As'!Oe'V~}`mJy<SqXcl11uJuV(^CZx|{;k/n?zpr")},
      {true, "BDDB86D4FBE84489FFB63F0F3E7D814B180A20ED5EC34A01E0506600F9B74CE6",
       asciiBytes("PMrX2]fs0pr^oF;03dA:Gu=!.Tp~Yf<{X^Dj#~'OMz0.a$]ti#UH:3MlX`"
                  "\\f8uC%rp.`={\"AmdAee6>h8`=Iaw")},
      {true, "3B27EE392836476FDE5FB1AEA1A40015562F29BBFCFCB5BF8B01859439936F3C",
       asciiBytes(" rfBW.K6$<41n~(Yurd%d|e?CqV{~o(+F=8G@5Y9?PI4S6oOwb]?MF0g*P%["
                  "6*@_c2\\P=Gb44\"0[McsO4UdPz^4")},
      {true, "5437E139972A905A75B7A4D04DE8ED08B534777377E10A9B214294E2C4D6ECA8",
       asciiBytes("zE,&v|667MR;'VOBkB&!6Dn`>~[-[L(PR, "
                  "<+z9&fKLe4l|1=&dnQvVSO\\Rx`zI#:CEHnJQBc,8pqG4JXkR\\bknx")},
      {true, "F8E61BBCACE1D174B5B5FD9DFCB5CB1E01FCD3A045B15062ED8AC56BE79EEE81",
       asciiBytes(
           "{c6{!4ova({^j#vokDdk%)D2M?Gfh "
           "@UZFDE;s15L8;`l04X3MQ+,6y(I8[^OANqVR1x,Vf?W#K+)(*rl88\"Y?jGw")},
      {true, "26D36F4091747FA368B4D501D2CEF0EAF37CA34562642D0D41C85E87AF21680A",
       asciiBytes("LkA%jnR)Y/Wv=Aa/mMQ\"P^<s}H#j'm:n=\\uwq|/"
                  "\\2LWxPq0^'+a?akuds'Ye0!_4p&5cU,N1x:pB_9\\t$^+j<W#l|6")},
      {true, "6C7358E175A0DAB4F47A5B5F0299FD65DBEE19D46EF6A07124484FF94516DCF6",
       asciiBytes("B4e[x=mmWA4LG(pj|-J?-tD\"##F7)F'\\;~Mnc{#-P$j.n& "
                  "!(LSU?r?%6IQr%)4FkTWR!z\"h];$;+b+ M~NTAz(9VFv")},
      {true, "96D9800D4CAF4B28B89CF0FCA11B3493D8784428D9A6CB9E083CA989920E69AB",
       asciiBytes("]w%e&R'h4&Gp&dx3868z^`*uXN( "
                  "LH`\\`u9^0x!6NTr'2[,uVnr.ua^$vMcx|F:,dO,K+{:Ceyc.xt(\"jp~"
                  "ZO8^i;W'l")},
      {true, "6FCC499431BA24C8248500846242486EAE9C085B55DF0660803CD4CE53A68BE1",
       asciiBytes(
           "#IB7G;z[gC``_Kn}3IXr<G}\"s4JGWuV(kp/"
           "`U4C't*jgS`:zKNWt\"{uUWN*o{Y5n-YHq8H:+49L'NJ~0w}+F_?a-]auM{")},
      {true, "F42C1C1AFB621E5501624CCA52A48A42B512E81279B1AB4F9388949ECBAF689A",
       asciiBytes("*=V-Ju+8Zbz@Fg'rm]s-0^F-yrveLYZ~S*w257srzjPNK-Ef>;m)uuG*"
                  "z9X5v2}}>Ci.RbU|gNSHgn=jO~DRIr=fc{JjX{")},
      {true, "970AE595CE90FE53048CCEDDE023FA56EC467A5EA709F4B03A595CD11060A229",
       asciiBytes("N']+.M+SdX8#z\"#?@t(?;<T?i/#KZf>F]hJ,D?W?(@,/"
                  "RatubO8w;\"$Yh8l7vBx%+|QEw W7Tr@9?B`^Ap^o}wf'+#'r+?h")},
      {true, "4EBB13A3A5380C8A370A6790A06A67B11EBE062C66B8CF6733BDF274906FAA42",
       asciiBytes("-n\\g58b\"%/s/S\\-\"0%;=bAqRrc*KTImxBt$QZU7pNKc{A)49<{ "
                  ",);\\?Rf!\"FBpOeMAN|#-it5Qomr~\\3J%Gi#h/efqPREI ")},
      {true, "DF1163CE27BED691ED01709063DB5A9D88738B1B8D3DC949E81121BF4C0C3D2A",
       asciiBytes("Fw:4:d]VAB[!yS#ai?>Q6IL)sD!.'4n0NZk2sJfHoMz[Jh(QFMKZv[3`mO!"
                  "NhpLy)zrUkkx1:),a%p#=a{+g4~A} Ryj#%nER")},
      {true, "5F5684144D37A7C1C9AE7839915A8E423ACDCF196F17C805DBB38C80A2D97066",
       asciiBytes("-SAZekEn.7!<'0OMX(u\"mbj~y{XXk,^sE;eWaQjw3/o'\"b/"
                  ".|Jn?z@Jucnhuf{THUB['B+ZUb @1ljult *;D$PIA]'zQ9kS|;")},
      {true, "5C88A9DD0DBA90C14FE112F2AFACF23B8DD0F067E5B96F1923B58DC588980602",
       asciiBytes("d9);3|=p4|;J:8yZmtKS_IA6Q0$Xe~-&${Fl|g,'Ul($BoC!^Ee?aL71No="
                  "aD)U;sE_i'F\"fFc,G>_!>yO9 Y|)Q(5`Eemfs<1Y")},
      {true, "57E147092652F6310B349DA857A0A04FA5A81C3FF6B6C147B96053276FAD2808",
       asciiBytes("&tg\\?OjxC2pKN8k5p%3U9b'Pn`0WTGk@#ZKRAm!(&](yO})y]A{sA2=jr:~"
                  "/w5UasX5-DD~y[#e((#b9hkU!^9QZy<y[k3PRp`]`")},
      {true, "F195A1B8142AFB88612E895D6F2B7A9C7A5307354143208AA3BA6347A0B7B5FB",
       asciiBytes("|//>o=*M`%,yhL\\A:92\\BQyo*NK4.Y "
                  "hB7??W-Y\\:dKi&k3(4e+%nQ0uXHrX&R':B+&E;3+[RSH&XG_Bna_7,#,"
                  "qQXWKc(R00Gbo4")},
      {true, "8A26DD0A05703B61C350B0425218EB6FD255AC344E675790FF98617C4E45BD28",
       asciiBytes("$-}9cDBZ=OO&cz "
                  "w]lp^)hM\"ZuS^juNBOX7`VOX#G9QjgSAth{->t8eG2|}M6)5N|?6'sxY=]"
                  "\"QBGb>d}@]vb\"jlh1<x/[02_;7wof")},
      {true, "3342E0DBA1804FC0354ECF9FDF038B8E895FDB6BAFCCAD5649BEE6F4FEC77F52",
       asciiBytes(
           "E<.\\rm!3cS|%S},rTc/+5Yzu#!1w5U\\oZi}5!->w4{}'Xg[x!EdY<9Vm!1Qb/"
           "1QR#.BWc&&|@T pD!%GeQN7v)j\"I(ci($l>;i{MVU+")},
      {true, "38AB1076CBC6CF480A876EA97EF5D0B8153FF37F03C88082BD099C4EC1A0DAA2",
       asciiBytes(
           "r% PRU{.'\":0,/+EU7|X2nf_d(u(K>76xJ7TLF4?-j[!>k=PG+tfHo\"\\c'RDfu' "
           "g%Omy[>wuWpO/4~'dU$N7]m\\`|(Ku!?0Y?BVatL(")},
      {true, "FF399B076029580B15B98C6AAB415AD0368516277DCC6C46599737699BE482E2",
       asciiBytes("E#~g,KAstGfhoDa5s-s;F5xU0i,1 "
                  "gOv1D]\"Ykd2APypljIG`cMmbtPSt@nR+*eB6\\'f@O@V&ER1Ds8f:(R_i~!"
                  "RmG99onN.beKNFA,J:")},
      {true, "DCA172A9C1FC860FC4DB69A2EE2063407709E9DF94B3E505F8AFA17180AE271A",
       asciiBytes(
           "XGOT]u7#Q&L@;Pf^!Mpn\",gi>O^K$U+Bw`?w0ma?MuH!/S#m/"
           "&KkutHZm1+l|S:L>oU,[, k,yiA\"Eh|**22Jo#^~wT1vbXf2W}53+A8E9")},
      {true, "17993BB536779AA26D48343D4926FD0C0FDEF240E8495CCAEE875CC3318D82F8",
       asciiBytes(" gE<\\aDfZF,3bFw2\":J>rh!.}cW@rLu+!S`KlZvUe?]lh&{-p2xB>"
                  "1f\\wYE/Hg6Hl/ew$D.xT6Oc.kT[2ei5y.i?SE?K{hkm%SoAge:S={f")},
      {true, "EC4E5BC8E25D3D3F2DBB93388DD100DCA2294268F2CADC9E19EBC159D45C8FC0",
       asciiBytes(
           "^3GL>rL\"WAHS1\\4$e@)\"}Xn2@-? '\\osD@dQ9J6?hF0SPz+cSeANRMm'c "
           "\"X($qC{rrPu?tkJj+6/32y035t?9Yg|M$$~eJkuCN*ySJR-3*%")},
      {true, "5DFEB92EE1DDE7C86C72C36F6D36BC960D3AC0F7B0EA9B2E3DC3465BA670DBDB",
       asciiBytes("VP*N#`!6o;jp)s%4<4I]3052,9~|rpL>Z862[^qd<'&V:'Sz&Y:i.J]r%]-"
                  "N9)T?UfNJjL\"\\{]B6G;@pQGe86<+o<d;z&Y7F,M#A?(M%Z89]e")},
      {true, "300CB029A81F0F5049E81F4239FC22F3A981D7F068B55D0E333BA44A883DAFE3",
       asciiBytes(
           "s/E^J/UD732KvxFdb=dd/@Y=sR}aLHmtSf]p!kJ54/0mP0{\"`UHpaHMX6Y` "
           "qPY@1M}xT7Pj4kC,XGZk<e^0^$^5]@>Vz>,\"pJNQFZ],[,I&x0")},
      {true, "F14315E3DE249C4916AAFE9897F8273A74F5F2F0D87542C5BF5D95E038F29DF3",
       asciiBytes("{n}OCeKt|@x|pv9mt5p&dl/"
                  "_N5lb3'a$d8#{~KtmZ7cEV1pr'_H[LCP;{V:iWouj)(W59{jgvY-2GQ("
                  "2uT18*Tq2$2zJO~cBz.J]H\\9)3PgB:i\\")},
      {true, "C4B14E1B490FF511C928BAF324F797DB204D418C01E0988BA1CDEA3892147D8A",
       asciiBytes("3b_QU(G3{mh+x7^P|x+4!c5&w^HVgZ>D91<:Q(#|\\3kS%qXBmU-)Ov7`"
                  "Lsf=HD4%9qF^mg`L$C/{vjP}@j{T)u'ZBIX[C0RdOcdxYH@bV?8nR{bo")},
      {true, "586F36F94AF92E9DDC3812870997D477F6EF0873B4CCAF3D776304FD29C43678",
       asciiBytes(
           "5XCtj\\iNsU8PDBLb\"v4OTl4iMVQd<nOCM9o{H_7e,oP3dIMGY=*M^6%gU0sTl{X#"
           "i*iBZxDny&[7ecEp TKh9Eta=C<|lu2r[#m~a%s]OzGEMt3UV")},
      {true, "33704360941E55A8A32A66E9E2BF7D196C5537D9AB69A01C5C10C9705C28BC4B",
       asciiBytes(
           "8;{>`qwjLl9ic+[HafvW%Tz=L[_bmy=?yRWT_0Odna|L5|+R#m/"
           "TdvT;(u&Sq1{'qSbM{Cp~e*r @2Cq^?W,K0HnDe_6Q*#tJ'X(:[P!{Q\"b)fh2Z<")},
      {true, "E1590CCB24A2E156BBDDDFECC2DA94989B41B3451B8115876131642E2636D053",
       asciiBytes(
           "]D~Xh4964^PwE#I&jB=u_Lxm7qG{F>m%N\"I3wI|GJ#k\\I,zg^!n=\\H\\c2{#}</"
           "E(=Fo[:rP)=ZcI^cI6y|K1p#WQvB-5[LZI. G7\\'^s8>=zFeUd5HS")},
      {true, "63DB933B46088190CDB36D0E9B82D32FA8AA3C626EB85AFD00B2D071A5F0207C",
       asciiBytes(
           "qM;hZ^Q<4l,5EOaV3Ob6`,[)&k6\\ibY+jE&l[&xxi2>^Z}Mymj0K=^w8*~>4="
           "C3bQ4vn9^ \\J1y+--yWh'{Av:n[D:~vu^Ww6Wv|Kh%_g.VE5\\o;(HDq")},
      {true, "0F1BB25A70CEEE0A6326D9296626DDA0CEE8CB231B4D58709EC96849A410293F",
       asciiBytes(";0%IFh)EPr$<E*mo[96RFq$/F@?@N/SZYxUtB9GVC "
                  "vgZHiKwQ7~`$aXYELRmTf{:|3%MF_vuU))hvm4%L(`'[6FxE8O "
                  "JKon$}=J68^8d5}y]5<p`xzY")},
      {true, "EF50F7D7434FDE29C4B1F0AFAB4F6E857B9106DF32B4236B3AB3DCDB6318AB6D",
       asciiBytes(
           "ghT&.ix!&BT9rh>qEzBs#[6C$'5N,]dhzU=G#>7&D(L4^n6[Dz@czk!5-jC7|GY]"
           "2OnT*)v6Ep7(k[6K(?@\\aaCwW`1'7a3]<[DM#2w\\CJwiodi~[_D}n%")},
      {true, "A102BBCABD9576D4ED65C25C693A907825C459AD37341877734C6FF1BFBAE55F",
       asciiBytes(">q<DS'&H5(*A.4MkHI2Y}k0s1AO\\iD "
                  "$jvVDqF-SxN4iO>a^%TzU3Rxw=3t1A^fWd{ZbPV@ShQMu5g8C!VcUO0U~"
                  "uLS.Rr4N{`4eWVk9qXX:YYjKF+YJ}#[")},
      {true, "FC96F2BE60B43BC959F69C3470EF641D3880FC0FFA94C9C7862C50E78B83AABB",
       asciiBytes(
           "`n/"
           "3Le.a=$Qx\\LUv(4{+nsv`8i2|hp_~G82WUYkT)f$cN*AkLp9bm?3ja|h)gh|"
           "kG4eHxR\\r(h\"x_kt2_.T,z!'F@#!wy:c%<4(uli946wIk2\"&\"<f\\>bH H")},
      {true, "3306C473B847F8CFE5414CFD07CD9C7C82108E73DF0EE477326043FC2962D829",
       asciiBytes("c BiT^da62YF7U0M3Zu1j%$F|DPEH)M3.NgzYe3z@nrbu<[? "
                  "FB#2=4;|W;94cU@{u,TZ0HlX7 "
                  "qnQ*e&o\":C43AnW2S5>Tf0KB=jM|nE52A-bJft\"Ee$Fe9v")},
      {true, "40C9D807DC580F02B6B1707978FAA224CA3327137AE2B404988441AE20E893A9",
       asciiBytes(
           "/i%!YTIj$nEku$Z1k|#S,d;C?1*h3}:AMQ%SBMH'hN-Ax&T.H;#vy]}s2ML`\".5&S%"
           "e$!9TYct;lNlQD+tpL=`:>DhyIWvy]\"Bp@C@H/p&z`mPC|V1vUSvE?)&")},
      {true, "584EED5C85AECD9A15B51E27898E1385423482C24E04B45B67FEBC48BF27D6D1",
       asciiBytes("^Etd8,p\"w2CZKcxB92ltY+.[7p1ZUH`YK\\e|1`BWYxSCuS m8.M&k!Z% "
                  "!jRHxB+7Z-)]lb#m:W_8&fuP%/"
                  ")o!E3|}+\\69WA?Rx=9S.R};J<*5Lt:vY7h}>c+Zh")},
      {true, "ABDCB903AD06AD2390FE022479F3DFACCF9681158FBB8252BBCBB93A8E649C63",
       asciiBytes("kNTDAA@w3k.:D{)F:PUC_V0J| "
                  "b]),JdYKD4A/"
                  "?0*v\\08RV~HK(7TfTb1q9F\"C~n;\"7DQ~!N25`\"]U3\\B\\q("
                  "0p\"UwNk({jN. ;B\"S+/na(s>\\&u30[y7^aLM[)e#")},
      {true, "FCB82031934F1D3B3ADCE0616C729B75231DC26703630F994C68F1B5A71E1B4C",
       asciiBytes("FwVM,sn\"#w>\\y[9krCH%^W/"
                  ".>\"W3p%7+{lgIMvZpsz,K4#|9Rs[>p\"|o{7CmX'SRTnCr:I.uR#<Vq:"
                  "dKI$4\"d+GfXt=:yL*Wz~tR6lMCw)JOoHl}nLkjyoJB48X{G")},
      {true, "E214C459DFC66AB4E36D4BA625F9A95805147749743DA27F515A04EA616A0C18",
       asciiBytes(
           ">6xVDIi]tN*Y'pp6`3i7Hb\\.Z>\"D6O&uV$vG=_gdEfXwYeAiD%g$F=.qw9@)V4d*"
           "R\"[5#m.r'\"^s-CL~H'o:,!5}|.)yUjH/yBlK^LV}v?47FdY,RG:#`Su-<~sKci")},
      {true, "107C1212954CD5AC0435CABDE0E9D1135EC07D8C42802A00B571F2C8292775B8",
       asciiBytes("T3#F!B+w`l($](cORXRw5f'/N1S.5sLfbfNhcuSRi0*5E5b$?M%_QGcI/"
                  "+=Xlwo1~WewY|Y7q.j<rE95-\\?-EteTnO!hh4V\"ucruMc\\N6-@CDDDZ  "
                  "Rv'`M1KGX(69G")},
      {true, "2F04A53A7A557AB8D986BA961EEB417C33D1C411399092AFFA33ED0F13F5C504",
       asciiBytes("[SX]k-w:t,bsdb$(hvN9CJcCR]ln<tpVi0#]-1D\"2SF~t/"
                  "Y2ITCYWVm|3DvVpK-q{@KrP*+32ZqcMx=`(=##(#53W%[(Y)on.@<g0JO,"
                  "ic(A_nCF<@ItmGO)S^45ZWBT")},
  };
  for (const TestCase &tc : singleCases) {
    const Sha256Hash actualHash =
        Sha256::getHash(tc.message.data(), tc.message.size());
    assert((actualHash == Sha256Hash(tc.expectedHash)) == tc.matches);
    numTestCases++;
  }
}

static void testDoubleHash() {
  // Double SHA-256 hash
  const vector<TestCase> doubleCases{
      {true, "56944C5D3F98413EF45CF54545538103CC9F298E0575820AD3591376E2E0F65D",
       asciiBytes("")},
      {true, "58636C3EC08C12D55AEDDA056D602D5BCCA72D8DF6A69B519B72D32DC2428B4F",
       asciiBytes("abc")},
      {true, "AF63952F8155CBB708B3B24997440992C95EBD5814FB843AAC4D95687FE1FF0C",
       asciiBytes("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq")},
      {false,
       "55B852781B9995A44C939B64E441AE2724B96F99C8F4FB9A141CFC9842C4B0E3",
       asciiBytes("")},
      {false,
       "AD1500F261FF10B49C7A1796A36103B02322AE5DDE404141EACF018FBF1678BA",
       asciiBytes("abc")},
  };
  for (const TestCase &tc : doubleCases) {
    const Sha256Hash actualHash =
        Sha256::getDoubleHash(tc.message.data(), tc.message.size());
    assert((actualHash == Sha256Hash(tc.expectedHash)) == tc.matches);
    numTestCases++;
  }
}

static void testHmac() {
  // HMAC-SHA-256 message authentication code
  struct HmacCase {
    bool matches;
    const char *expectedHash;  // In byte-reversed order
    Bytes key;
    Bytes message;
  };
  const vector<HmacCase> hmacCases{
      // From RFC 4231
      {true, "F7CF322E6C37E926A73D83C900C21D882BF10BAFCEAFA85C5338DBD8614C34B0",
       hexBytes("0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B"),
       asciiBytes("Hi There")},
      {true, "4338EC64B958EC9D8339279D083F005AC77595082624046A4E7560BF46C1DC5B",
       asciiBytes("Jefe"), asciiBytes("what do ya want for nothing?")},
      {true, "FE65D5CE145563D922C1F83E8B095929A78191D0EBB84D85460E80361EA93E77",
       hexBytes("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"),
       hexBytes("DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD"
                "DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD")},
      {true, "5B662967F43F2E7A07F878E5A3FAF0853A08F2999881CCA40E3C449A388A5582",
       hexBytes("0102030405060708090A0B0C0D0E0F10111213141516171819"),
       hexBytes("CDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCD"
                "CDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCD")},
      {true, "C520CDB0AA60F8938BEF8A6A0A7C6FFA2B5555296C790C6EE00E10737416B6A3",
       hexBytes("0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C"),
       asciiBytes("Test With Truncation")},
      {true, "547FE30E0F04460514C5283721C60B8E7FB7F5CBAA268A0D7FB6E01E5931E460",
       hexBytes(
           "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
           "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
           "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
           "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"),
       asciiBytes("Test Using Larger Than Block-Size Key - Hash Key First")},
      {true, "E2353A5C53517F8A9313074F6463DCBF44E9B0D5BC5F6327CB2F941BA7FF099B",
       hexBytes(
           "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
           "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
           "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
           "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"),
       asciiBytes("This is a test using a larger than block-size key and a "
                  "larger than block-size data. The key needs to be hashed "
                  "before being used by the HMAC algorithm.")},
      {false,
       "F7CF322E6C37E926A73D83C900C21D882BF10BAFCEAFA85C5338DBD8614C34B0",
       hexBytes("0B0B0B0B0B4B0B0B0B0B0B0B0B0B0B0B0B0B0B0B"),
       asciiBytes("Hi There")},
      {false,
       "F7CF322E6C37E926A73D83C900C21D982BF10BAFCEAFA85C5338DBD8614C34B0",
       hexBytes("0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B"),
       asciiBytes("Hi There")},
      {false,
       "F7CF322E6C37E926A73D83C900C21D882BF10BAFCEAFA85C5338DBD8614C34B0",
       hexBytes("0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B"),
       asciiBytes("HI There")},
  };
  for (const HmacCase &tc : hmacCases) {
    const Sha256Hash actualHash = Sha256::getHmac(
        tc.key.data(), tc.key.size(), tc.message.data(), tc.message.size());
    assert((actualHash == Sha256Hash(tc.expectedHash)) == tc.matches);
    numTestCases++;
  }
}

static void ap(Sha256 &hasher, const char *msg) {
  std::vector<std::uint8_t> temp(msg, msg + std::strlen(msg));
  hasher.append(temp.data(), temp.size());
}

static void testStatefulHasher() {
  {
    Sha256 h;
    assert(h.getHash() == Sha256Hash("55B852781B9995A44C939B64E441AE2724B96F99C"
                                     "8F4FB9A141CFC9842C4B0E3"));
    numTestCases++;
  }
  {
    Sha256 h;
    ap(h, "a");
    assert(h.getHash() == Sha256Hash("BB48EEAF857780B9724E7C14F8EF86A74DDC239AB"
                                     "331C2FACABD1BCA128197CA"));
    numTestCases++;
  }
  {
    Sha256 h;
    ap(h, "a");
    ap(h, "bc");
    assert(h.getHash() == Sha256Hash("AD1500F261FF10B49C7A1796A36103B02322AE5DD"
                                     "E404141EACF018FBF1678BA"));
    numTestCases++;
  }
  {
    Sha256 h;
    ap(h, "ab");
    ap(h, "c");
    assert(h.getHash() == Sha256Hash("AD1500F261FF10B49C7A1796A36103B02322AE5DD"
                                     "E404141EACF018FBF1678BA"));
    numTestCases++;
  }
  {
    Sha256 h;
    ap(h, "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
    assert(h.getHash() == Sha256Hash("C106DB19D4EDECF66721FF6459E43CA339603E0C9"
                                     "326C0E5B83806D2616A8D24"));
    numTestCases++;
  }
  {
    Sha256 h;
    ap(h, "abcdbcdecdefde");
    ap(h, "fgefghfghighijhijkijkljklmklmnlmnomnopnopq");
    assert(h.getHash() == Sha256Hash("C106DB19D4EDECF66721FF6459E43CA339603E0C9"
                                     "326C0E5B83806D2616A8D24"));
    numTestCases++;
  }
}

int main() {
  testSingleHash();
  testDoubleHash();
  testHmac();
  testStatefulHasher();
  std::printf("All %d test cases passed\n", numTestCases);
  return EXIT_SUCCESS;
}
