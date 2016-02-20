//by tianlin 2001.5.1
inherit NPC;
inherit F_MASTER;
void create()
{
        set_name("八神庵", ({"bashen an", "bashen"}));
        set("gender", "男性" );
        set("age", 30);
        set("long", "他是拳皇里面杰出人物一提起他无人不只．他还是草雉京的死敌.\n");
        set("combat_exp", 320000);
  set("daoxing", 3200000);

        set("attitude", "friendly");
        create_family("格斗之王", 2, "首徒");
	set("int", 25+random(5));
        set_skill("unarmed", 280);
        set_skill("iori-kuihua", 280);
        set_skill("dodge", 280);
        set_skill("parry", 280);
        set_skill("spells", 200);  
        set_skill("iori-spells", 200);  
        set_skill("literate", 10);
        set_skill("dodge", 280);  
        set_skill("force", 280);   

        map_skill("spells", "iori-spells");
        map_skill("unarmed", "iori-kuihua");


        set("per", 30);
        set("max_kee", 62500);
        set("max_gin", 2400);
        set("max_sen", 32400);
        set("force", 12450);
        set("max_force", 4300);
        set("force_factor", 350);
        set("mana", 2450);
        set("max_mana", 2300);
        set("mana_factor", 108);
	set("chat_chance_combat", 50);
	set("chat_msg_combat", ({	
              (: cast_spell, "bazhinu" :),
              (: perform_action,"unarmed","xiaofeng" :),
              (: perform_action,"unarmed", "kuihua" :),
        }) );

        setup();
       // carry_object("/d/kof/obj/cloth")->wear();
}
void attempt_apprentice(object ob)
{
	if ( ((int)ob->query("combat_exp") < 1000)) {
	command("say " + RANK_D->query_respect(ob) +
"你想拜我,还差的远呢.你再练两年再来拜我吧.");
	return;
	}
        command("say 很好，" + RANK_D->query_respect(ob) +
"我看你和我挺投缘的.我就手下你了.你一定要加油练他日帮我杀了草雉京\n");
        command("recruit " + ob->query("id") );
}
// int recruit_apprentice(object ob)
// {
       // if( ::recruit_apprentice(ob) )
               // ob->set("class", "taoist");
// }

�