//By tianlin@mhxy for 2002.1.17

inherit SSERVER;
#include <ansi.h>


int cast(object me)
{
        int howlong;
        int spell,tt;
        spell=me->query_skill("spells")/2 + me->query_skill("buddhism");
        if(spell < 100)
                return notify_fail("�㻹ûѧ��������������\n");

        if (me->query_temp("no_heal_up/yinshen"))
                return notify_fail("���Ѿ�����������!\n");

        if ( ((tt=(int)me->query_temp("lastyinshen")) <= time()) && 
             (tt+20 > time()))
                return notify_fail("��ո�����������������Ϣһ�°�!\n");

        if( (int)me->query("mana") < 2*(int)me->query_skill("spells"))
                return notify_fail("��ķ��������ˣ�\n");

        if( (int)me->query("sen") < 50 )
                return notify_fail("��ľ����޷����У�\n");

        message_vision("$N�૵����˼������\n", me);

        if( random(me->query("max_mana")) < 200 ) {
                me->add("mana",-(int)me->query_skill("spells"));
                me->receive_damage("sen",10);
                message("vision", "����ʲôҲû�з�����\n", environment(me));
                return 5+random(5);
        }

        me->add("mana", -2*(int)me->query_skill("spells"));
        me->receive_damage("sen", 20);

        howlong = 15 + random((me->query_skill("spells") -100));
//      if (!me->query("env/invisibility"))
                call_out("free", howlong, me, howlong);
//      me->set_temp("yinshentime", howlong+(int)me->query_temp("yinshentime"));

        me->set("env/invisibility", 1);
        me->set_temp("no_heal_up/yinshen",1);
        
        message_vision(HIW"\nֻ��һ���׹�������$N�ټ����ޡ�\n\n"NOR, me);
        
        return 5+random(5);
}

void free(object user, int howlong)
{
        if(!user) return;
        user->delete_temp("no_heal_up/yinshen");
        if (!user->query("env/invisibility")) return;
/*      if (user->query_temp("yinshentime") - howlong) {
                user->set_temp("yinshentime", 
                        user->query_temp("yinshentime") - howlong);
                call_out("free", user->query_temp("yinshentime"), 
                        user, user->query_temp("yinshentime"));
                return;
                }
*/
//      user->delete_temp("yinshentime");
        user->delete("env/invisibility");      
        user->save();
        message_vision(HIW"\n�׹�����֮��$N���ֳ������Ρ�\n\n"NOR, user);
        user->set_temp("lastyinshen",time());
        return;
}
