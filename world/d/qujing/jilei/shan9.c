//Cracked by Roath
// create by snowcat.c 12/15/1997

inherit ROOM;

void create ()
{
  set ("short", "ɽ��");
  set ("long", @LONG

ֻ��ɽ��·�գ����ϻ��ǹ�ͺͺ���ҹ����һƬ��������ľ��
ɭ�֣�����Х�ش�����������ҰԳ����ԶԶ�س����е���
�˵����ľ���

LONG);

  set("exits", ([
        "northwest"   : __DIR__"shan8",
        "east"   : __DIR__"shan10",
      ]));
  set("outdoors", __DIR__);

  setup();
}


