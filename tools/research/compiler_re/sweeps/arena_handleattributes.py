# tools/sweep.py spec: cGameModeArena::HandleAttributes. CD2 shares one stack slot between the address-taken `void *p`
# of case 0 and the float `mem` of cases 3/4 (0x50); our build puts p at 0x54.
SOURCE = 'src/GameManagement/cGameModeArena.cpp'
TARGETS = [('?HandleAttributes@cGameModeArena@', 0x8284E6D8, 1120)]
S = SOURCE
DECL = '                    void *p;\n'
ASSIGN = '                        p = Editor::cGUIDLinker<cGameModePrototype>::LinkToObject(g);\n'
SWITCH = '            switch (it->GetCommandId())\n'
C3 = '                { float mem = it->GetAs_float(); RwMemNative32(&mem, 4); m_fToDPhase = mem; }\n'
C4 = '                { float mem = it->GetAs_float(); RwMemNative32(&mem, 4); m_fToDPeriod = mem; }\n'
FUNC = '    void cGameModeArena::HandleAttributes(const RWS::CAttributePacket &packet)\n'
HELPER = ('    static inline float NativeFloat(const RWS::CAttributeCommand *pCmd)\n'
          '    {\n        float f = pCmd->GetAs_float();\n        RwMemNative32(&f, 4);\n        return f;\n    }\n\n')
VARIANTS = {
    'p_in_loop': [(S, DECL, ''), (S, ASSIGN, ASSIGN.replace('p = ', 'void *p = '))],
    'p_init_null': [(S, DECL, '                    void *p = 0;\n')],
    'p_function_scope': [(S, DECL, ''), (S, '        cGMMResource::HandleAttributes(packet);\n',
                                         '        void *p;\n        cGMMResource::HandleAttributes(packet);\n')],
    'mem_loop_scope': [(S, SWITCH, '            float mem;\n' + SWITCH),
                       (S, C3, C3.replace('float mem = ', 'mem = ')), (S, C4, C4.replace('float mem = ', 'mem = '))],
    'mem_helper': [(S, FUNC, HELPER + FUNC),
                   (S, C3, '                m_fToDPhase = NativeFloat(it.operator->());\n'),
                   (S, C4, '                m_fToDPeriod = NativeFloat(it.operator->());\n')],
    'p_in_loop+mem_helper': [(S, DECL, ''), (S, ASSIGN, ASSIGN.replace('p = ', 'void *p = ')), (S, FUNC, HELPER + FUNC),
                             (S, C3, '                m_fToDPhase = NativeFloat(it.operator->());\n'),
                             (S, C4, '                m_fToDPeriod = NativeFloat(it.operator->());\n')],
}
