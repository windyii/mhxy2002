#include <ansi.h>

void copy_npc(int sum);
void set_status(object ob,int exp,int skill);
string query_site();
void verdict_end();
int query_children(string arg);
void verdict_time();
void set_hj_startT(int i);
int query_hj_startT();
void juedou();

string *factions=({"��ѩɽ","����ɽ","�¹�","��ׯ��","����ɽ","���޵ظ�","���ƶ�","�޵׶�","��������","��ɽ��","��˿��","������","������"});
string faction;     //��Ź��������
int Cnpcend, count = 0;
int hj_startT = 0;
object lead;

//�ƽ�ϵͳ������������
void disaster(int sum)
{
   count = sum;
        LOGIN_D->set_dienpc(-1);
        set_hj_startT(time());
        faction = factions[count];
        shout(HIR"����ؽ١�"MAG"������֯��ʼѪϴ��"+chinese_number(count+1)+"��Ŀ�꡾"HIR+faction+MAG"����\n"NOR);
        shout(HIW"����ؽ١����ڴ�е�ǰ�������ڿ�ʼ�������״̬���κ��˲����������ӣ�\n"NOR);
        call_out("copy_npc",1);
}

//����EXP and SKILL��ָ�������ȵ�ɱ��(pker)
void copy_npc(int sum)
{
        object ob, *user;
        string site, domain;
        int i, j, exp, skill, lead_exp=0;
        int t=0;

        user = users();
        j = sizeof(user);
        Cnpcend = 0;
        for (i=0;i<j;i++) {
                if (faction!="������" && user[i]->query("family/family_name")!=faction) {
                        t++;
                        continue;
                }
                if (!user[i]) {t++;continue;}
                exp = (int) user[i]->query("combat_exp");
                skill = (int) user[i]->query_skill("parry",1);
                if (lead_exp < exp) {lead_exp = exp;lead = user[i];}
                if (skill < 1) skill = 5;
                if (exp < 10000)
                        ob = new("/d/haojie/npc/pker1");
                else if (exp < 30000)
                        ob = new("/d/haojie/npc/pker2");
                else if (exp < 50000)
                        ob = new("/d/haojie/npc/pker3");
                else if (exp < 80000)
                        ob = new("/d/haojie/npc/pker4");
                else if (exp < 150000)
                        ob = new("/d/haojie/npc/pker5");
                else if (exp < 300000)
                        ob = new("/d/haojie/npc/pker6");
                else if (exp < 500000)
                        ob = new("/d/haojie/npc/pker7");
                else if (exp < 800000)
                        ob = new("/d/haojie/npc/pker8");
                else
                        ob = new("/d/haojie/npc/pker9");


                set_status(ob,exp,skill);
                site = query_site();
                domain = domain_file(site);
                ob->set("domain",domain);
                ob->move(site);
                message_vision("$N�����ɷ�����˹�����\n",ob);
        }

        if (t>=j) {
//                shout(HIR"����ؽ١�"MAG"����"+faction+"���¿���һ�ˣ�ħ�粻ս��ʤ��һ��������"+faction+"��\n"NOR);
//                shout(HIW"����ؽ١�ħ���������������Ц����û�뵽������׵��֣�����������Ҳ����������������һ����\n"NOR);
                shout(HIW"����ؽ١�������ʱ�����ˣ����ڽ������״̬��\n"NOR);
                LOGIN_D->set_madlock(0);
                call_out("disaster",10,count+1);
                return;
        }
        if (sum<3)
                call_out("copy_npc",20,++sum);
        else {
                Cnpcend = 1;
                call_out("verdict_time",1800);
        }
}

//����player��EXP and SKILL����pker��EXP and SKILL
void set_status(object ob,int exp,int skill)
{
        ob->set("combat_exp",exp);
        ob->set_skill("parry",skill);
}

//���������������pker����ŵص�
string query_site()
{
        mapping sites=([
                "��ѩɽ":               ({"/d/xueshan/wuchang-c","/d/xueshan/wuchang-e","/d/xueshan/eroad2","/d/xueshan/xuejie"}),
                "����ɽ":               ({"/d/lingtai/lantao","/d/lingtai/jingge","/d/lingtai/jingtang","/d/lingtai/baixi"}),
                "��ׯ��":               ({"/d/qujing/wuzhuang/jiangjing","/d/qujing/wuzhuang/shaoxiang","/d/qujing/wuzhuang/juyuan","/d/qujing/wuzhuang/xunzhen"}),
                "����ɽ":               ({"/d/nanhai/xiaoyuan","/d/nanhai/guangchang","/d/nanhai/zoulang","/d/nanhai/tingjing"}),
                "���޵ظ�":             ({"/d/death/naiheqiao","/d/death/bidouya","/d/death/zhengtang","/d/death/pingyang"}),
                  "�¹�":               ({"/d/moon/snow","/d/moon/tree2","/d/moon/wulang","/d/moon/huilang"}),
                "��������":             ({"/d/sea/huayuan1","/d/sea/inside6","/d/sea/shiwu","/d/sea/girl4"}),
                "��ɽ��":             ({"/d/shushan/path1","/d/shushan/houshan","/d/shushan/jinglou","/d/shushan/feipu"}),
                "��˿��":             ({"/d/qujing/pansi/ling2","/d/qujing/pansi/jiandi","/d/qujing/pansi/menqian","/d/qujing/pansi/muxiang"}),
                "������":               ({"/d/city/fangzhang","/d/city/guozi","/d/city/baihu-w2","/d/city/zhuque-s2","/d/city/qinglong-e3"}),
                "������":               ({"/d/jjf/gate","/d/jjf/keting","/d/jjf/kitchen_road2","/d/jjf/ne_garden","/d/jjf/main_cabinet"}),
                "�޵׶�":               ({"/d/qujing/wudidong/firemount-wudidong1","/d/qujing/wudidong/tang-gate","/d/qujing/wudidong/square2","/d/qujing/wudidong/bedroom-gate"}),
                "���ƶ�":               ({"/d/qujing/kusong/guaishiya","/d/qujing/kusong/songlin4","/d/qujing/kusong/songlin3","/d/qujing/kusong/songlin1","/d/qujing/wuji/shandao5"}),
        ]);

        return sites[faction][random(sizeof(sites[faction]))];
}

//�жϺƽ��Ƿ�ƽϢ
void verdict_end()
{
        int sum = 0;

        if ( !Cnpcend ) return;
        sum += query_children("/d/haojie/npc/pker9.c");
        sum += query_children("/d/haojie/npc/pker8.c");
        sum += query_children("/d/haojie/npc/pker7.c");
        sum += query_children("/d/haojie/npc/pker6.c");
        sum += query_children("/d/haojie/npc/pker5.c");
        sum += query_children("/d/haojie/npc/pker4.c");
        sum += query_children("/d/haojie/npc/pker3.c");
        sum += query_children("/d/haojie/npc/pker2.c");
        sum += query_children("/d/haojie/npc/pker1.c");
        if (sum > 1) return;

        if (count+1 != sizeof(factions)) {
//                shout(HIR"����ؽ١�"MAG+faction+"������"+lead->name()+"�Ĵ����£�ɱ�õ��������ɾ�����ܶ��ӣ�\n"NOR);
                shout(HIW"����ؽ١�ħ�������������棺�����̵ģ�������Ӳ�����ȣ�\n"NOR);
//                shout(HIW"����ؽ١���ʱ���˵��ˣ�������Ƶõ����⣬��ʱ�������״̬��\n"NOR);
                call_out("disaster",20,count+1);
        }
        else {
//                shout(HIR"����ؽ١�"MAG"�������ɽӳ����ˣ���"+lead->name()+"�Ĵ����£����ڴ����ħ�����ı�������ָֻ������յ�ƽ����\n"NOR);
                shout(HIW"����ؽ١��з���ܣ��˼�ָ�ƽ�����������״̬��\n"NOR);
//                shout(HIW"����ؽ١�ħ�������������������У��Ҳ��������Ҳ����������Ҳ�����������\n"NOR);
                call_out("juedou",5);
        }
        LOGIN_D->set_madlock(0);

}
void juedou()
{
        object ob;
        object *user;
        int i, exp, skill, killer = 0;

        user = users();
        for(i=0;i<sizeof(user);i++)
                if (user[i]->query_temp("hj_killer") > killer) lead = user[i];

        ob = new("/d/haojie/obj/zhanshu.c");
        ob->move(lead);
        message_vision(HIY"һ��ս��Ʈ����$N����ǰ��\n"NOR,lead);
        shout(HIM"����ؽ١�"+"��˵"+lead->name()+HIM"�õ���һ��ħ�����������������ս�顣\n"NOR);
//        shout(HIM"����ؽ١�"+"��˵"+lead->name()+HIM"�õ���һ��ħ�����������������ս�顣\n"NOR);
        exp = lead->query("combat_exp");
        skill = lead->query_skill("parry",1);
        ob = new("/d/haojie/npc/tianshaxing.c");
        ob->set("pk_target",lead);
        set_status(ob,exp,skill);
        ob->move("/d/city/center.c");
        message_vision("$N�����ɷ�����˹�����\n",ob);
}

//ȡָ��pker������
int query_children(string arg)
{
        object *ch;
        int i,sum = 0;

        ch = children(arg);
        for(i=0;i<sizeof(ch);i++)
                if(environment(ch[i])) sum++;
        return sum;
}

//��ʱ�жϺƽٷ�����ʱ���Ƿ񳬹����ޣ������������ҳͷ�
void verdict_time()
{
        object *user;
        int i, exp, parry, force;

//���úƽٵ�����Ϊ30����(1800��)
        if( (time()-hj_startT) < 1800 ) {
                remove_call_out("verdict_time");
                call_out("verdict_time",60);
                return;
        }
        if (!LOGIN_D->get_madlock()) return;

        user = users();
        if (faction != "������")
                for(i=0;i<sizeof(user);i++) {
                        if (user[i]->query("family/family_name") != faction) continue;
                        if (!user[i]) continue;
//                      exp = (int) user[i]->query("combat_exp") * 0.97;
                        parry = (int) user[i]->query_skill("parry",1) * 0.99;
                        force = (int) user[i]->query_skill("force",1) * 0.99;
//                      if (exp > 1000) user[i]->set("combat_exp",exp)
                        if (parry > 5) user[i]->set_skill("parry",parry);
                        if (force > 5) user[i]->set_skill("force",force);
                
        else    for(i=0;i<sizeof(user);i++) 
                        if (!user[i]) continue;
                        exp = (int) user[i]->query("combat_exp") * 0.97;
                        parry = (int) user[i]->query("balance") * 0.75;
                        if (exp > 1000) user[i]->set("combat_exp",exp);
                        if (parry > 0) user[i]->set("balance",parry);
                
        if (count+1 != sizeof(factions)) {
//                shout(HIR"����ؽ١�"MAG+faction+"������ս֮�£��������أ��Ӵ������伣��\n"NOR);
//                shout(HIW"����ؽ١�ħ�����������������һ������һ����\n"NOR);
                shout(HIW"����ؽ١�������ʱ�����ˣ����ڽ������״̬��\n"NOR);
//                shout(HIW"����ؽ١�������ʱ�����ˣ����ڽ������״̬��\n"NOR);
                }
        
        else 
         {
//                shout(HIR"����ؽ١�"MAG"��Ȼ���ɷ���ɱ�У���������̫�󣬻��ǰ���������һʱ���ȷ�Ѫ�꣬����һƬ�찵��\n"NOR);
//                shout(HIW"����ؽ١�ħ��������ȫʤ������һƬ�ڰ������ڽ������״̬����ҿ�������!\n"NOR);
        }
        
        LOGIN_D->set_madlock(0);
}
}
void set_hj_startT(int i)
{
        hj_startT = i;
}
int query_hj_startT()
{
        return hj_startT;
}
