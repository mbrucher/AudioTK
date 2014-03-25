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
<node TEXT="Wave" ID="ID_684320580" CREATED="1391880823695" MODIFIED="1395776883905">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="libsndfile" ID="ID_1688625522" CREATED="1395776865029" MODIFIED="1395776877665">
<icon BUILTIN="button_ok"/>
</node>
</node>
<node TEXT="Outputs" ID="ID_930469082" CREATED="1391880783401" MODIFIED="1391880785285">
<node TEXT="Wav" ID="ID_608818497" CREATED="1391880815415" MODIFIED="1395776880907">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="libsndfile" ID="ID_988853474" CREATED="1395776870126" MODIFIED="1395776874778">
<icon BUILTIN="button_ok"/>
</node>
</node>
<node TEXT="Core" ID="ID_1974077192" CREATED="1391880785936" MODIFIED="1391880790052">
<node TEXT="I/O conversion" ID="ID_1407202419" CREATED="1395777119051" MODIFIED="1395777131517">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Lag handling" ID="ID_912495434" CREATED="1395777049225" MODIFIED="1395777076701"/>
</node>
<node TEXT="Mock" ID="ID_3708272" CREATED="1391880790768" MODIFIED="1391880792093">
<node TEXT="White noise generator" ID="ID_355593601" CREATED="1391880840404" MODIFIED="1391880845936"/>
<node TEXT="Sinus generator" ID="ID_1654533231" CREATED="1395776832981" MODIFIED="1395776863220">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="FFT check" ID="ID_75194125" CREATED="1395776839589" MODIFIED="1395776860626">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Triangle generator" ID="ID_1452782039" CREATED="1395776842229" MODIFIED="1395776858530">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Triangle checker" ID="ID_1091000415" CREATED="1395776849798" MODIFIED="1395776855885">
<icon BUILTIN="button_ok"/>
</node>
</node>
<node TEXT="Tools" ID="ID_1857774892" CREATED="1395776810092" MODIFIED="1395776811544">
<node TEXT="Pan" ID="ID_295886939" CREATED="1395776812637" MODIFIED="1395776913542">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Sum" ID="ID_864094639" CREATED="1395776818457" MODIFIED="1395776911144">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Volume" ID="ID_358732341" CREATED="1395776820210" MODIFIED="1395776908354">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Downsampling" ID="ID_581251876" CREATED="1395776893748" MODIFIED="1395776905729">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Oversampling" ID="ID_639984442" CREATED="1395776898842" MODIFIED="1395776903124">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Optimizer" ID="ID_841054843" CREATED="1395776915459" MODIFIED="1395776919302">
<node TEXT="Scalar Newton" ID="ID_1878042242" CREATED="1395776920330" MODIFIED="1395776933791">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Vector Newton" ID="ID_1524410543" CREATED="1395776924516" MODIFIED="1395776931711"/>
</node>
</node>
<node TEXT="EQ" ID="ID_1077608646" CREATED="1391880792576" MODIFIED="1391880793476">
<node TEXT="Second Order" ID="ID_1755313817" CREATED="1391880827470" MODIFIED="1395776889873">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Bessel" ID="ID_1906874507" CREATED="1395776794549" MODIFIED="1395776797683"/>
<node TEXT="Butterworth" ID="ID_324795407" CREATED="1395776798284" MODIFIED="1395776801345"/>
<node TEXT="FIR" ID="ID_1922442511" CREATED="1395776801932" MODIFIED="1395776806825"/>
</node>
<node TEXT="Distortion" ID="ID_900647788" CREATED="1395776976316" MODIFIED="1395776979784">
<node TEXT="Simple overdrive" ID="ID_700366864" CREATED="1395776980285" MODIFIED="1395777004168">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Tube" ID="ID_1136898156" CREATED="1395776991563" MODIFIED="1395776998552"/>
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
