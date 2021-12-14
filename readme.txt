Vamvakousis Giwrgos
csd4112

an pid=-1 pernoume to trexon task_struct me thn get get_current() ap to asm/current.h.
an pid < -1 return EINVAL.
else psaxnoume to task_struct me pid==pid kai tsekaroume mesw ths check_list() an to
task_struct einai thugatriko. H check_list() xrhsimopoiei to struct list_head pou periexetai sto kathe task_struct kai
xrhsimopoiwntas to list_for_each kai to list_entry vlepoume ta paidia enos task kai an to task me pid==pid einai thugatriko.
an pid >= -1 anathetoume sto task_struct tis times twn parametrwn.
An apo tis parametrous paroume curr->deadline <= curr->computation_time epistrefoume EINVAL
