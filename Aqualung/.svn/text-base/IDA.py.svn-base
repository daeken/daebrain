import idaapi, idautils, idc

class IDA(object):
    def getFunc(self, ea=None, next=False):
        if ea == None:
            ea = idaapi.get_screen_ea()
        
        if next:
            ea = idc.NextFunction(ea)
            if ea == -1:
                return (0xFFFFFFFFL, 0xFFFFFFFFL)
        
        if ea < 0:
            return (0xFFFFFFFFL, 0xFFFFFFFFL)
        elif idc.GetFunctionName(ea) == idc.GetFunctionName(idc.PrevAddr(ea)):
            ea = idc.PrevFunction(ea)
        return (ea, idc.FindFuncEnd(ea))
    
    def getInsn(self, ea):
        mnem = idaapi.generate_disasm_line(ea).split(' ', 1)[0][2:-2]
        
        ops = []
        for i in range(6):
            op = idc.GetOpnd(ea, i)
            if not op:
                break
            
            ops.append(op)
        
        return mnem, tuple(ops), idautils.CodeRefsFrom(ea, True)
    
    def getString(self, ea):
        s = ''
        while True:
            b = idc.Byte(ea)
            if b == 0:
                return s
            s += chr(b)
            ea += 1
