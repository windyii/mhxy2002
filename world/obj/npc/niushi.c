// niushi.c
#include <ansi.h>
inherit NPC;
void create()
{
	object ob1, ob2;
string *order = ({"��", "��", "��", "��"});
	set_name((order[random(4)]) + "ëʭ", ({ "niushi"}) );
	set("long", "û����ʭ����ȥţ�ͺ���������ϸ���ҡ�\n");
	set("attitude", "friendly");
	set("max_gin", 400);
	set("max_kee", 400);
set("max_sen", 400);
	set("max_mana", 500);
	set("mana", 500);
	set("str", 40);
	set("cor", 30);
	set("cps", 25);
	set("combat_exp", 100000);
	set_skill("stick", 100);
	set_skill("parry", 100);
	set_skill("dodge", 100);
	setup();
	ob1=carry_object("/d/obj/armor/shoupi");
	ob1->wear();
	ob1->set("no_sell", "�ƹ�����һ�۵����ⶫ��һ�������ӵ�Ʒ����Ҫ����Ҫ��\n");
	ob2=carry_object("/d/obj/weapon/stick/xiangmo");
	ob2->wield();
	ob2->set("no_sell", "�ƹ�����һ�۵����ⶫ��һ�������ӵ�Ʒ����Ҫ����Ҫ��\n");
}
int heal_up()
{
	if( environment() && !is_fighting() ) {
		call_out("leave", 1);
		return 1;
}
	return ::heal_up() + 1;
}
void leave()
{
	message("vision",
		RED + name() + "˵�����㶨�������Ѫȥ����\n\n"
+ name() + "����������ϴ�����ϡ�\n" NOR, environment(),
		this_object() );
	destruct(this_object());
}
void invocation(object who)
{
	int i;
	object *enemy;
	message("vision",
		RED "ֻ��ž����һ����һ�ź�ⱬ����һ����Ŀ������ţʭ�����˵��ϡ�\n\n"
+ name() + "˵���������Ǻ��棬�����Ǻ��棡\n" NOR,
		environment(), this_object() );
	enemy = who->query_enemy();
	i = sizeof(enemy);
	while(i--) {
		if( enemy[i] && living(enemy[i]) ) {
			kill_ob(enemy[i]);
			if( userp(enemy[i]) ) enemy[i]->fight_ob(this_object());
			else enemy[i]->kill_ob(this_object());
}
}
	set_leader(who);
}