<map version="freeplane 1.2.0">
<!--To view this file, download free mind mapping software Freeplane from http://freeplane.sourceforge.net -->
<node TEXT="ATK" ID="ID_1723255651" CREATED="1283093380553" MODIFIED="1391880678520"><hook NAME="MapStyle">
    <conditional_styles>
        <conditional_style ACTIVE="true" LOCALIZED_STYLE_REF="AutomaticLayout.level,1" LAST="false">
            <node_level_condition VALUE="1" MATCH_CASE="false" MATCH_APPROXIMATELY="false" COMPARATION_RESULT="0" SUCCEED="true"/>
        </conditional_style>
        <conditional_style ACTIVE="true" LOCALIZED_STYLE_REF="AutomaticLayout.level,2" LAST="false">
            <node_level_condition VALUE="2" MATCH_CASE="false" MATCH_APPROXIMATELY="false" COMPARATION_RESULT="0" SUCCEED="true"/>
        </conditional_style>
        <conditional_style ACTIVE="true" LOCALIZED_STYLE_REF="AutomaticLayout.level,3" LAST="false">
            <node_level_condition VALUE="3" MATCH_CASE="false" MATCH_APPROXIMATELY="false" COMPARATION_RESULT="0" SUCCEED="true"/>
        </conditional_style>
        <conditional_style ACTIVE="true" LOCALIZED_STYLE_REF="AutomaticLayout.level,4" LAST="false">
            <node_level_condition VALUE="4" MATCH_CASE="false" MATCH_APPROXIMATELY="false" COMPARATION_RESULT="0" SUCCEED="true"/>
        </conditional_style>
    </conditional_styles>

<map_styles>
<stylenode LOCALIZED_TEXT="styles.root_node">
<stylenode LOCALIZED_TEXT="styles.predefined" POSITION="right">
<stylenode LOCALIZED_TEXT="default" MAX_WIDTH="600" COLOR="#000000" STYLE="as_parent">
<font NAME="SansSerif" SIZE="10" BOLD="false" ITALIC="false"/>
</stylenode>
<stylenode LOCALIZED_TEXT="defaultstyle.details"/>
<stylenode LOCALIZED_TEXT="defaultstyle.note"/>
<stylenode LOCALIZED_TEXT="defaultstyle.floating">
<edge STYLE="hide_edge"/>
<cloud COLOR="#f0f0f0" SHAPE="ROUND_RECT"/>
</stylenode>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.user-defined" POSITION="right">
<stylenode LOCALIZED_TEXT="styles.topic" COLOR="#18898b" STYLE="fork">
<font NAME="Liberation Sans" SIZE="10" BOLD="true"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.subtopic" COLOR="#cc3300" STYLE="fork">
<font NAME="Liberation Sans" SIZE="10" BOLD="true"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.subsubtopic" COLOR="#669900">
<font NAME="Liberation Sans" SIZE="10" BOLD="true"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.important">
<icon BUILTIN="yes"/>
</stylenode>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.AutomaticLayout" POSITION="right">
<stylenode LOCALIZED_TEXT="AutomaticLayout.level.root" COLOR="#000000">
<font SIZE="18"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,1" COLOR="#18898b">
<font SIZE="16"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,2" COLOR="#cc3300">
<font SIZE="14"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,3" COLOR="#669900">
<font SIZE="12"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,4" COLOR="#3333ff">
<font SIZE="10"/>
</stylenode>
</stylenode>
</stylenode>
</map_styles>
</hook>
<hook NAME="AutomaticEdgeColor" COUNTER="1"/>
<hook NAME="accessories/plugins/AutomaticLayout.properties" VALUE="ALL"/>
<node TEXT="C++" POSITION="right" ID="ID_768989959" CREATED="1391880696698" MODIFIED="1391880725917">
<edge COLOR="#7c7c00"/>
<cloud COLOR="#f0f0f0" SHAPE="ARC"/>
<node TEXT="Inputs" ID="ID_433901627" CREATED="1391880780872" MODIFIED="1391880782853">
<node TEXT="Wave" ID="ID_684320580" CREATED="1391880823695" MODIFIED="1391880825466"/>
</node>
<node TEXT="Outputs" ID="ID_930469082" CREATED="1391880783401" MODIFIED="1391880785285">
<node TEXT="Wav" ID="ID_608818497" CREATED="1391880815415" MODIFIED="1391880817978"/>
</node>
<node TEXT="Core" ID="ID_1974077192" CREATED="1391880785936" MODIFIED="1391880790052"/>
<node TEXT="Mock" ID="ID_3708272" CREATED="1391880790768" MODIFIED="1391880792093">
<node TEXT="White noise generator" ID="ID_355593601" CREATED="1391880840404" MODIFIED="1391880845936"/>
</node>
<node TEXT="EQ" ID="ID_1077608646" CREATED="1391880792576" MODIFIED="1391880793476">
<node TEXT="Second Order" ID="ID_1755313817" CREATED="1391880827470" MODIFIED="1391880831986"/>
</node>
<node TEXT="Dynamics" ID="ID_1198712523" CREATED="1391880793912" MODIFIED="1391880800651"/>
</node>
<node TEXT="Python" POSITION="right" ID="ID_1591627391" CREATED="1391880715389" MODIFIED="1391880722615">
<edge COLOR="#ff0000"/>
<cloud COLOR="#f0f0f0" SHAPE="ARC"/>
<node TEXT="I/O in Numpy" ID="ID_1068189790" CREATED="1391880729781" MODIFIED="1391880744828"/>
<node TEXT="Interface in Python" ID="ID_1495402697" CREATED="1391880745743" MODIFIED="1391880752452"/>
</node>
</node>
</map>
