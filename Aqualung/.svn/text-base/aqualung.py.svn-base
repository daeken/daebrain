"""
Aqualung -- An experimental ARM decompiler
Copyright 2007 Cody Brocious (cody DOT brocious AT gmail DOT com)

Required:
 * IDA Pro (tested with 5.0 Advanced)
 * IDAPython (latest)

To use:
 * Enter the function you wish to decompile
 * Press alt-9
 * Select aqualung.py

This will automatically decompile all functions referenced from
the current one, recursively.
"""

import IDA
reload(IDA)
from IDA import IDA

import idaapi, idc

class Aqualung(object):
    def __init__(self):
        print 'Aqualung -- An experimental ARM decompiler'
        print 'Copyright 2007 Cody Brocious (cody DOT brocious AT gmail DOT com)'
        
        self.shiftMap = dict(
            ASL='<<',
            ASR='>>',
            LSL='<<',
            LSR='>>',
        )
        
        self.arithMap = dict(
            ADD='+',
            AND='&',
            BIC='&',
            LSL='<<',
            LSR='>>',
            MUL='*',
            ORR='|',
            SUB='-',
            SUBS='-',
            EOR='^',
        )
        
        self.suffixMap = dict(
            NE='!=',
            EQ='==',
            GE='>=',
            PL='>=',
            CS='<=',
            GT='>',
            VC='>',
            HI='>',
            CC='<',
            LT='<',
            MI='<',
            LS='<',
            VS='<',
        )
        
        self.ida = IDA()

        self.decompiled = []
        
        self.func = self.ida.getFunc()
        self.cmp = None
        self.decompile(self.func[0])
        
        if idaapi.get_screen_ea() not in self.decompiled:
            self.decompile(idaapi.get_screen_ea())
    
    def decompile(self, ea, regs=None):
        if regs == None:
            self.regs = dict(
                r0 ='arg0', r1 ='arg1', r2 ='arg2', r3 =None,
                r4 =None, r5 =None, r6 =None, r7 =None,
                r8 =None, r9 =None, r10=None, r11=None,
                r12=None, r13=None, r14=None, r15=None,
                trash=None
            )
        else:
            self.regs = regs
        
        if ea in self.decompiled:
            return
        
        # print 'Decompiling %08X' % ea
        
        while True:
            if ea in self.decompiled:
                break
            self.decompiled.append(ea)
            self.ea = ea
            
            if ea == idaapi.get_screen_ea():
                for name in self.regs:
                    print '%s == %s' % (name, self.regs[name])
            
            mnem, ops, branches = self.ida.getInsn(ea)
            self.dispatch(ea, mnem, ops)
            
            if len(branches) == 0:
                break
            elif len(branches) == 1:
                ea = branches[0]
                continue
            else:
                curfunc = self.ida.getFunc(ea)
                for branch in branches:
                    nextfunc = self.ida.getFunc(branch)
                    
                    if nextfunc != curfunc:
                        self.decompile(branch)
                    else:
                        self.decompile(branch, regs=self.regs)
                break
    
    def dispatch(self, ea, mnem, ops):
        cond = ''
        
        if (mnem.startswith('LDR') or mnem.startswith('STR')) and len(mnem) == 6:
            mnem, size = mnem[:-1], mnem[-1]
        else:
            size = None
        
        for suffix in self.suffixMap:
            if mnem.endswith(suffix):
                tempmnem = mnem[:-len(suffix)]
                if not self.findHandler(tempmnem, nonCmp=True):
                    continue
                mnem = tempmnem
                if self.cmp:
                    cond = '%s %s %s' % (self.cmp[0], self.suffixMap[suffix], self.cmp[1])
                    cond = 'if(%s) ' % ' && '.join(self.cmp[2] + [cond])
                break
        
        if size:
            mnem += size
        
        handler = self.findHandler(mnem)
        if handler != None:
            out = handler(mnem, ops)
            if out != None and out != False:
                #idc.MakeComm(ea, cond + out)
                idc.MakeComm(ea, '')
        else:
            pass # print 'Unhandled instruction:', mnem, ', '.join(ops)
    
    def findHandler(self, mnem, nonCmp=False):
        if mnem in self.arithMap:
            handler = self.arithmetic
        elif not nonCmp and (mnem.startswith('CMP') or mnem.startswith('CMN') or mnem.startswith('TST')):
            handler = self.compare
        else:
            try:
                handler = getattr(self, mnem)
            except:
                handler = None
        return handler
    
    def allnum(self, inp):
        for c in inp:
            if c not in '0123456789':
                return False
        return True
    
    def isConstant(self, value):
        if value[0] == '"' and value[-1] == '"':
            return True
        elif self.allnum(value):
            return True
        elif value[:2] == '0x':
            return True
        return False
    
    def addParens(self, value):
        value = value.lower()
        if value[0] == 'r' and len(value) <= 3:
            return value
        elif value[0] == '(' and value[-1] == ')':
            return value
        
        return '(%s)' % value
    
    def processOp(self, op, noRef=False, out=False):
        temp = op.rsplit(',', 1)
        if len(temp) > 1 and temp[1][1] == 'S':
            op = self.processOp(temp[0])
            value = self.processOp(temp[1][3:])
            
            return '(%s %s %s)' % (op, self.shiftMap[temp[1][:3]], value)
        
        if op[0] == '[' and op[-1] == ']':
            ops = op[1:-1].split(',')
            if len(ops) > 1:
                return self.addParens(' + '.join(self.processOp(op) for op in ops))
            else:
                return ops[0]
        elif op[0] == '#':
            if self.allnum(op[1:]):
                return '0x%x' % eval(op[1:] + 'L')
            else:
                return op[1:]
        elif op[0] == '=':
            if noRef:
                return (op[1:], )
            else:
                return '&' + op[1:]
        else:
            oplower = op.lower()
            
            if out or oplower not in self.regs or self.regs[oplower] == None:
                return op
            
            return self.regs[oplower]
    
    def arithmetic(self, mnem, ops):
        out = self.processOp(ops[0], out=True)
        outlower = out.lower()
        if outlower not in self.regs:
            outlower = 'trash'
        
        if len(ops) == 2:
            left = out
            right = self.processOp(ops[1])
        else:
            left = self.processOp(ops[1])
            right = self.processOp(ops[2])
        
        if mnem == 'BIC':
            right = '~%s' % right
        
        if right == '0x0':
            self.regs[out.lower()] = left
            return '%s = %s;' % (out, left)
        
        if out != left:
            arith = '%s %s %s' % (left, self.arithMap[mnem], right)
            self.regs[outlower] = self.addParens(arith)
            return '%s = %s;' % (out, arith)
        else:
            self.regs[outlower] = '%s %s %s' % (self.processOp(out), self.arithMap[mnem], right)
            if right[0] == '(':
                right = right.lstrip('(').rstrip(')')
            return '%s %s= %s;' % (out, self.arithMap[mnem], right)
    
    def compare(self, mnem, ops):
        op1, op2 = self.processOp(ops[0]), self.processOp(ops[1])
        
        if mnem.startswith('CMN'):
            op2 = '-' + op2
        elif mnem.startswith('TST'):
            op1 = '(%s & %s)' % (op1, op2)
        
        if len(mnem) == 3 or not self.cmp:
            self.cmp = op1, op2, []
        else:
            self.cmp[2].append('%s %s %s' % (self.cmp[0], self.suffixMap[mnem[3:]], self.cmp[1]))
            self.cmp = op1, op2, self.cmp[2]
    
    def ADR(self, mnem, ops):
        out = self.processOp(ops[0], out=True)
        addr = idc.LocByName(ops[1])
        type = idc.GetStringType(addr)
        if type == 0:
            data = self.ida.getString(addr)
            data = '"%s"' % `"'" + data`[2:-1]
        else:
            data = ops[1]
        
        return '%s = %s;' % (out, data)
    
    def B(self, mnem, ops):
        return ''

    def BX(self, mnem, ops):
        return ''
    
    def BL(self, mnem, ops):
        args = []
        
        for reg in ('r0', 'r1', 'r2'):
            if self.regs[reg] == None:
                args.append(reg.upper())
            else:
                args.append(self.regs[reg])
        
        call = '%s(%s)' % (ops[0], ', '.join(args))
        self.regs['r0'] = call
        
        return call
    BLX = BL
    
    def LDR(self, mnem, ops):
        out = self.processOp(ops[0], out=True)
        outlower = out.lower()
        if outlower not in self.regs:
            outlower = 'trash'
        
        right = self.processOp(ops[1], noRef=True)

        addr = idc.LocByName(ops[1][1:])
        type = idc.GetStringType(addr)
        if type == 0:
            right = self.ida.getString(addr)
            right = ('"%s"' % `"'" + right`[2:-1], )
        
        if right.__class__ == tuple:
            right = right[0]
        else:
            right = '*' + right
        
        self.regs[outlower] = right
        
        return '%s = %s;' % (out, right)
    
    def LDRB(self, mnem, ops):
        out = self.processOp(ops[0], out=True)
        outlower = out.lower()
        if outlower not in self.regs:
            outlower = 'trash'
        
        addr = self.processOp(ops[1])
        addr = '*(uchar *) %s' % addr
        
        self.regs[outlower] = addr
        
        return '%s = %s;' % (out, addr)
    
    def LDRH(self, mnem, ops):
        out = self.processOp(ops[0], out=True)
        outlower = out.lower()
        if outlower not in self.regs:
            outlower = 'trash'
        
        addr = self.processOp(ops[1])
        addr = '*(ushort *) %s' % addr
        
        self.regs[outlower] = addr
        
        return '%s = %s;' % (out, addr)
    
    def MOV(self, mnem, ops):
        out = self.processOp(ops[0], out=True)
        outlower = out.lower()
        if outlower not in self.regs:
            outlower = 'trash'
        
        value = self.processOp(ops[1])
        
        if not self.isConstant(value):
            self.regs[outlower] = self.addParens(value)
        else:
            self.regs[outlower] = None
        
        if value[0] == '(':
            value = value.lstrip('(').rstrip(')')
        
        if value.startswith(out + ' '):
            op, value = value[len(out)+1:].split(' ', 1)
            return '%s %s= %s;' % (out, op, value)
        else:
            return '%s = %s;' % (out, value)

    MOVL = MOV
    MOVS = MOV

    def STR(self, mnem, ops):
        value = self.processOp(ops[0])
        out = self.processOp(ops[1], out=True)
        
        return '*%s = %s;' % (out, value)
    
    def STRB(self, mnem, ops):
        value = self.processOp(ops[0])
        out = self.processOp(ops[1], out=True)
        return '*(uchar *) %s = %s;' % (out, value)
    
    def STRH(self, mnem, ops):
        value = self.processOp(ops[0])
        out = self.processOp(ops[1], out=True)
        return '*(ushort *) %s = %s;' % (out, value)
    
if __name__=='__main__':
    Aqualung()
