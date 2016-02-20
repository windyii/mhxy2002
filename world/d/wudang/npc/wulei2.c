// by LPG 19990926
// killme---- kill�Լ��ĳ�ħ����
// wulei.c
inherit NPC;
#include "newplace.h";
#include <ansi.h>
string kill_apply();
void copy_status(object me, object ob);
void copy_weapon(object me, object ob);
//string killme_success ();
int fresh=1;
string *names = ({
  "��",
  "��",
  "��",
});
string *namesw = ({
  "��",
  "ľ",
  "ˮ",
  "��",
  "��",
});
void create()
{
	set_name(namesw[random(sizeof(namesw))]+"����", ({"shen jiang","jiang"}));
	set("current_player","none of us");
	setup();
	carry_object("/d/obj/weapon/hammer/bahammer")->wield();
	carry_object("/d/wudang/obj/whiterobe")->wear();
}
void init()
{
   object me = this_object();
   if (me->query("current_player")=="none of us")
   me->set("inquiry", ([
     "name" : "��Ҳ��֪���Լ���˭�����ܸ�����ô��\n",
     "here" : "���Ｔ��������Ｔ������ֺα�Ҫ�ʣ�\n",
     "kill" : (: kill_apply :),
     "��ħ" : (: kill_apply :),
   ]) );
   me->reset_me(me);    
   me->setup();
}
void reset_me (object me)
{
   int i;
   object *inv;
   mapping skill_status, map_status;
   string *skillnames, *mapnames;
   reset_eval_cost();
   if ( mapp(map_status = me->query_skill_map()) )
   {
     mapnames = keys(map_status);
     for(i=0; i<sizeof(mapnames); i++)
     {
        me->map_skill(mapnames[i]);
     }
   }
   if ( mapp(skill_status = me->query_skills()) )
   {
     skillnames = keys(skill_status);
     for(i=0; i<sizeof(skillnames); i++)  
     {
        me->delete_skill(skillnames[i]);
     }
   }
   inv = all_inventory(me);
   for(i=0; i<sizeof(inv); i++)
   {
     destruct (inv[i]);
   }
	me->set_name(namesw[random(sizeof(namesw))]+"����", ({"shen jiang","jiang"}));
	me->set("title", "�������");
	me->set("long", "�������������е�һ����\n");
	me->set("gender", "����");
        me->set("age",31);
	me->set("attitude", "heroism");
	me->set("str", 28);
	me->set("mana", 3000);
	me->set("max_mana", 3000);
	me->set("force", 4500);
	me->set("max_force", 4500);
	me->set("combat_exp", 1500000);
	me->set_skill("force", 300);
	me->set_skill("dodge", 300);
	me->set_skill("unarmed", 300);
	me->set_skill("parry", 300);
	me->set_skill("hammer", 300);
	me->set_skill("kaishan-chui", 300);
	me->set_skill("dao", 300);
	me->set_skill("spells", 300);
	me->map_skill("spells", "dao");
	me->map_skill("hammer", "kaishan-chui");
	me->set("short",me->query("name")+"("+capitalize(me->query("id"))+")");
	me->set("current_player","none of us");
	me->setup();
	reset_eval_cost();
	carry_object("/d/obj/weapon/hammer/bahammer")->wield();
	carry_object("/d/wudang/obj/whiterobe")->wear();
}
string kill_apply()
{
   object me = this_object();
   object ob = this_player();
   if ((me->query("id") != ob->query("id") + " yao") && (me->query("id") != "shen jiang"))
   	return "���ϴ�����\n";
   if (ob->query_temp("killme_applied"))
   	return "���ϸ�����û����أ�\n";
   ob->set_temp("killme_applied", "do");
   set("current_player","ok");
   tell_object(ob, CYN + me->query("name")+"��ɫ������������һ����ð��֮��(" + ob->query("id") + " yao)���ң���ȥ��������ǣ���\n"NOR);
   tell_object(ob, HIY"\n" + me->query("name") + "˵��һ���֣�����Ծ����ͷ��\n\n"NOR);
   copy_status(me,ob);
   me->move(newplace[random(sizeof(newplace))]);
   return "�ٺ٣������������\n";
}
void copy_status(object me, object ob)
{
//   object *inv;
   mapping hp_status, skill_status, map_status;
   string *sname, *mname,killme,killmeid;
   int i,j;//, weapon_cnt, armor_cnt;
   reset_eval_cost();
   hp_status = ob->query_entire_dbase();
   me->set("str", hp_status["str"]);
   me->set("per", hp_status["per"]);
   me->set("int", hp_status["int"]);
   me->set("age", hp_status["age"]);
   me->set_name(names[random(sizeof(names))], ({ob->query("id")+" yao","yao","guai","jing","gui"}));
   me->set("gender",	hp_status["gender"]);
   me->delete("title");
   me->set("short",	ob->query("name")+capitalize(me->query("name"))+"("+capitalize(me->query("id"))+")");
   me->set("combat_exp",hp_status["combat_exp"]+hp_status["combat_exp"]/15);
   me->set("chat_chance_combat",15);
   me->set("chat_msg_combat", ({
	(: cast_spell, "bighammer" :),
	(: cast_spell, "yinshen" :),
	(: cast_spell, "light" :),
	(: cast_spell, "thunder" :),
	(: cast_spell, "arrow" :),
	(: cast_spell, "gouhun" :),
	(: cast_spell, "freez" :),
	}) );//�����Ѷ�
   if(fresh==1) {
     fresh=0;
     me->set("eff_kee",  hp_status["eff_kee"]);
     me->set("kee",      hp_status["kee"]);
     me->set("eff_gin",  hp_status["eff_gin"]);
     me->set("gin",      hp_status["gin"]);
     me->set("eff_sen",  hp_status["eff_sen"]);
     me->set("sen",      hp_status["sen"]);
     me->set("eff_dx", me->query("combat_exp"));
     if(COMBAT_D->check_family(ob->query("family/family_name"))>0)
       me->set("eff_dx", -me->query("eff_dx"));
     if(me->query("combat_exp")>10000)
       me->set("nkgain",100); //maximum gain for killing yao.
   }
   me->set("max_gin",     hp_status["max_gin"]);
   me->set("max_kee",     hp_status["max_kee"]);
   me->set("max_sen",     hp_status["max_sen"]);
   me->set("max_force",   hp_status["max_force"]);
   me->set("max_mana",    hp_status["max_mana"]);
   me->set("eff_gin", me->query("max_gin"));
   me->set("gin",     me->query("max_gin"));
   me->set("eff_kee", me->query("max_kee"));
   me->set("kee",     me->query("max_kee"));
   me->set("eff_sen", me->query("max_sen"));
   me->set("sen",     me->query("max_sen"));
   me->set("force",   me->query("max_force")+me->query("max_force")*3/4);
   me->set("mana",    me->query("max_mana")+me->query("max_mana")*3/4);
   if(skill_status = me->query_skills()) {// delete old skills.
      sname  = keys(skill_status);
      j=sizeof(skill_status);
           for(i=0; i<j; i++) {me->delete_skill(sname[i]);}
   }
   if (skill_status = ob->query_skills() ) {//copy new skills.
      sname  = keys(skill_status);
      for(i=0; i<sizeof(skill_status); i++) {me->set_skill(sname[i], skill_status[sname[i]]);}
   }
   me->set("force_factor",me->query_skill("force")*3/4);
   me->set("mana_factor", me->query_skill("spells")*3/4);
   me->add_temp("apply/armor",(me->query_skill("spells")+me->query_skill("force"))/8);
   me->add_temp("apply/dodge",(me->query_skill("spells")+me->query_skill("force"))/8);
   me->add_temp("apply/damage",(me->query_skill("spells")+me->query_skill("force"))/15);
//   reset_eval_cost();
   //delete old skill mappings.
   if(map_status = me->query_skill_map()) {
     mname  = keys(map_status);
     j=sizeof(map_status);
     for(i=0; i<j; i++) {
       me->map_skill(mname[i]);
   }}
   //add new skill mappings.
   if (map_status = ob->query_skill_map()) {
     mname  = keys(map_status);
     for(i=0; i<sizeof(map_status); i++) {
     me->map_skill(mname[i], map_status[mname[i]]);
   }}
   copy_weapon(me,ob);//����װ��
   reset_eval_cost(); //   return 1;
   me->setup();
   me->save();
}
void copy_weapon(object me, object ob)
{
   object *inv;
   int i,j, weapon_cnt, armor_cnt;
   inv = all_inventory(me);
   for(i=0; i<sizeof(inv); i++) 
   {
     destruct(inv[i]);
   }
   // save once here, an external bug might stop the following
   me->setup();
   me->save();
   weapon_cnt = 0;
   armor_cnt = 0;
   inv = all_inventory(ob);
   for(i=0; i<sizeof(inv); i++) 
   {
     if ( !inv[i]->query_unique() && 
     inv[i]->query("skill_type") &&
     inv[i]->query("equipped") && !weapon_cnt ) 
     {
        object obj = new(base_name(inv[i]));
        if (obj)
        {
          if(obj->move(me)) // mon 8/13/97
          obj->wield();
        }
        me->set("weapon", base_name(inv[i]));
        weapon_cnt = 1;
     }
     else if ( !inv[i]->query_unique() && 
     !inv[i]->query("skill_type") && 
     inv[i]->query("equipped") && !armor_cnt ) 
     {
        object obj = new(base_name(inv[i]));
        if (obj)
        {
          if(obj->move(me))
          obj->wear();   //mon 8/13/97
        }
        me->set("armor", base_name(inv[i]));
        armor_cnt = 1;
     }
     else if( weapon_cnt && armor_cnt )
        break;
   }
}
int accept_object(object who, object ob)
{
   if (who->query_temp("killme_applied")){
   if ((ob->query("money_id") && ob->value() >= 1000) && 
   	((this_object()->query("id") == this_player()->query("id") + " yao") || this_object()->query("id") == "shen jiang"))
   {
     who->delete_temp("killme_applied");
     reset_me(this_object());
     tell_object(who,CYN"\n"+this_object()->query("name")+"���ٺ٣�����ͷ���һ����������ħ�ɲ��Ǽ����׵��¡�\n\n"NOR);
     return 1;
   }
   }else{
	tell_object(who,CYN"\n"+this_object()->query("name")+"����¸�ң����������£�������������ղ�û�����񰡣��ٺ٣�\n\n"NOR);
     return 1;
	}
   return 0;
}
void kill_ob (object ob)
{
	object me = this_object();
	message_vision (CYN"$N�ٺ�һЦ������������\n\n"NOR,me);
	copy_weapon(me,ob);
	set_temp("my_killer",ob);
	ob->kill_ob(me);
}
void unconcious()
{
	int i;
	object me = this_object();
	object ob = query_temp("my_killer");
	if( environment() ) {
		command("drop all");
		message("sound", HIY"\n"+me->query("name")+"����һ�����̳�����ȥ������\n\n"NOR, environment());
	}
	if ((ob) && (ob->query_temp("killme_applied") == "do"))
	{
		ob->set_temp("killme_applied","done");
		call_out ("dang_appearing",1,ob);
	}
	load_object("/obj/empty");
	me->move("/obj/empty");
	call_out ("destruct_me",3,me);
}
void die()
{
	unconcious();
}
void dang_appearing (object who)
{
  object dang = new ("/d/wudang/npc/master");
  dang->announce_success (who);
  destruct (dang); 
}

void destruct_me(object me)
{
  destruct(me);
}