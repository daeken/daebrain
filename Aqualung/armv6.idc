//armv6.idc

#include <idc.idc>

static condstr(cond)
{
  if (cond==0) return "EQ";
  else if (cond==0) return "EQ";
  else if (cond==1) return "NE";
  else if (cond==2) return "CS";
  else if (cond==3) return "CC";
  else if (cond==4) return "MI";
  else if (cond==5) return "PL";
  else if (cond==6) return "VS";
  else if (cond==7) return "VC";
  else if (cond==8) return "HI";
  else if (cond==9) return "LS";
  else if (cond==10) return "GE";
  else if (cond==11) return "LT";
  else if (cond==12) return "GT";
  else if (cond==13) return "LE";
  else if (cond==14) return "";//AL
  else return "";
}

static regstr(r)
{
  if (r==13) return "SP";
  else if (r==14) return "LR";
  else if (r==15) return "PC";
  else return form("R%d", r);
}

static decodev6(dw)
{
  auto rn, rm, rd, rr, m, cond, ins;
  if ((dw&0x0F8003F0) == 0x06800070)
  {
     cond = (dw>>28)&0xF; //[28:31]
     m = (dw>>20)&0x7;    //[20:22]
     rn = (dw>>16)&0xF;   //[16:19]
     rd = (dw>>12)&0xF;   //[12:15]
     rr = (dw>>10)&3;     //[10:11]
     rm = dw&0xF;         //[0:3]
     ins = "";
     if (m&7) ins="UXT"; else ins="SXT";
     m=m&3;
     if (rn!=15) ins = ins + "A";
     if (m==0) ins = ins + "B16";
     else if (m==2) ins = ins + "B";
     else if (m==3) ins = ins + "H";
     else {
       Message("bad armv6 instruction: %08X\n");
       return "";
     }
     ins = ins + condstr(cond);
     while (strlen(ins)<7) ins = ins + " ";
     ins = ins + " "+regstr(rd);
     if (rn!=15) ins = ins + ", "+regstr(rn);
     ins = ins + ", "+regstr(rm);
     if (rr!=0) ins = ins + form(", ROR #%d",rr);
  }
  //Message("%08X is %s\n", dw, ins);
  return ins;
}

#define MS_TAIL 0xFFF00000LU            // Mask of tail byte bits
#define TL_TSFT (4*5)                   // number of bits to shift to get
                                        // tail offsets
#define TL_TOFF MS_TAIL                 // Offset to next NOT-tail byte
#define MAX_TOFF (TL_TOFF>>TL_TSFT)     // Max offset can be written to flags

static main(void)
{
  auto a, e, i;
  a = SegStart(here);
  e = SegEnd(here);
  while (a<e)
  {
    if (!isCode(GetFlags(a)))
    {
      i = decodev6(Dword(a));
      if (i!="")
      {
        MakeUnkn(a, 0); // 0 == DOUNK_SIMPLE
        MakeDword(a);
        SetManualInsn(a, i);
        SetFlags(a, Byte(a)|FF_IVL|FF_CODE);
        SetFlags(a+1, Byte(a+1)|FF_IVL|FF_TAIL|(1<<TL_TSFT));
        SetFlags(a+2, Byte(a+1)|FF_IVL|FF_TAIL|(1<<TL_TSFT));
        SetFlags(a+3, Byte(a+1)|FF_IVL|FF_TAIL|(1<<TL_TSFT));
        if (!isCode(GetFlags(a+4)))
        {
	  MakeUnkn(a+4, 0); // 0 == DOUNK_SIMPLE
          MakeCode(a+4);
        }
        AddCodeXref(a,a+4,fl_F|XREF_USER);    //flow to next instruction
        //if (isCode(GetFlags(a+4)))
       	  AddCodeXref(a-4,a,fl_F|XREF_USER);  //flow from previous instruction
       	//break;
      }
    }
    a = a+4;
  }
}
