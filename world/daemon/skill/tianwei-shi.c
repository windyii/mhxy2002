inherit SKILL;

string *dodge_msg = ({
        "����$n����Ʈ����һ�С������ơ��εض���һ��һ������\nԽ��Խ�ߣ��������ڣ���������رܿ�����һ����\n",
        "$n������ת��һʽ�������ơ���ȫ������������Ӱ����������������ϼ��\n$N���첻���䣬$n�������ӳ����⡣\n",
        "$n��������һ�Σ�һ�С������ơ����ڿն���ֱ�����������˿�ȥ��\n",
        "$n���۵��һ�С������ơ������μ��ˣ�����ǧ��㿪$N������һ����\n",
        "$n���һ��������ȫ�������Ƴ�һ�С���ɽ�ơ�����$N���ھ�һ����\nֻ�����ء���һ�����죬$n�ѽ��Ƶ�������������֮�⡣\n",
        "$n���λζ���һ�С������ơ���ȫ������������������Ӱ��\n$nԽ��Խ��������������γ�һ�����У���$N�����������Գ�����\n",
        "$n����������һ�С������ơ����ٶ����������٣���Ϊһ����⣬ԶԶ�˿���\n",
        "$nʹ�����ѵ��ơ������μ������������գ�����׾ٵض㿪��$N��һ�С�\n",
        "$n��Ӱ΢�����Ѿ���һ�С������ơ����������������У�����������\n",
        "$n�ڿ�һԾ��˫����ǰһ�ߣ�һ�С������ơ���һ���������㿪���ߡ�\n",
        "ֻ��$n��Ӱһ�Σ�һʽ����Ծ�ơ����Ų����꣬���ѱ����߳�֮�⡣\n",
        "����$nʹһ�С�ӥ���ơ�����������Ʈ�˿�ȥ�������Ƶ�$N���ᣡ\n",
});

int valid_enable(string usage)
{
        return (usage=="dodge");
}

int valid_learn(object me)
{
        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( (int)me->query("sen") < 50 )
                return notify_fail("��ľ���̫���ˣ�����������ʮ���ơ�\n");
        me->receive_damage("sen", 40);
        return 1;
}
