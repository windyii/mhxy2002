//tuoqiao.c by greenwc
#include <ansi.h>
inherit SSERVER;
int cast(object me, object target)
{
        string msg,start;
        int ap, dp, success;
        target = offensive_target(me);
        
        if( me->is_busy())
                return notify_fail("����æ���أ���Ӧ����ǰ���°ɡ�\n");

        if(me->query("family/family_name")!="��ɽ��")
                return notify_fail("������ɽ�Ĳ����á�����ѿǡ���\n");
        
        if(me->query("shushan/tuoqiao_cast")!=1)
                return notify_fail("�㻹û��ᡸ����ѿǡ���\n");

        if( (int)me->query("mana") < 100 )
                return notify_fail("��ķ��������ˣ�\n");

        if( (int)me->query("sen") < (int)me->query("max_sen")/5 )
                return notify_fail("�㾫��̫����Լ��о������䡣\n");

              if( (int)me->query_skill("xianfeng-spells", 1) < 20)
                             return notify_fail("��δ��ѧ�����ѿǡ�\n");
        ap=me->query_skill("spells")+me->query("max_mana")/10;
        if(target) dp=target->query_skill("spells")+target->query("max_mana")/10;

        if(!me->is_fighting() )
        {
             message_vision(YEL"$N�����³�����˿�ߣ������ΰ��ڼ��С�\n"NOR,me);
             message_vision(YEL"ֻ��һֻ����Ƽ���ɣ�ֻ���¼��Ʋ�˿��\n"NOR,me);
                me->add("sen", -me->query("max_sen")/8);
                me->add("mana", -80);
                success=1;
        }
        else
        {
msg=YEL"$N�����³�����˿�ߣ������ΰ��ڼ��С�\n"NOR;
                if(random(ap+dp)>dp/2)
                {
msg+=YEL"ֻ��һֻ����Ƽ���ɣ�ֻ���¼��Ʋ�˿��\n"NOR;
                        me->add("sen", -me->query("max_sen")/6);
                        me->add("mana", -50);
                        success=1;
                }
else msg+=YEL"��$n��Ϊ������ն�Ƽ�ǣ�����$Nս����һ����\n"NOR;
                me->add("mana", -50);
                message_vision(msg, me, target);
        }
        if(success)
        {
start="/d/shushan/shanmen";
me->move(start);
message("vision", YEL+me->name()+"����Ӱһ������ֻ��ʱһ���������ǰ��\n"NOR,
                                  environment(me), me);
tell_object(me, YEL"�������һ�ۣ��ٻ��ף��������￪�⡣\n"NOR);
                return 3+random(3);
        }
        return 5+random(5);
       
}