(**
 * Copyright (c) 2015, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the "hack" directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 *
 *)

(**
 * This is dead code; when the code in src/js/hh_ide.ml and
 * src/server/serverFindLocals.ml is removed, this can be removed also.
 *)

module PosSet = Set.Make(Pos)

let handle_lvar target_ident ident_refs line char_pos ident id _ =
  let l, start, end_ = Pos.info_pos (fst id) in
  if l = line && start <= char_pos && char_pos <= end_
  then target_ident := Some ident;
  let current_set =
    match Local_id.Map.get ident !ident_refs with
    | Some refs -> refs
    | None -> PosSet.empty
  in
  ident_refs :=
    Local_id.Map.add ident (PosSet.add (fst id) current_set) !ident_refs


let attach_hooks line char =
  let target_ident = ref None in
  let ident_refs = ref Local_id.Map.empty in
  let get_result () =
    match !target_ident with
    | Some ident ->
      PosSet.elements (Local_id.Map.find_unsafe ident !ident_refs)
    | None -> []
  in
  Naming_hooks.attach_lvar_hook (handle_lvar target_ident ident_refs line char);
  get_result

let detach_hooks () =
  Naming_hooks.remove_all_hooks ()
