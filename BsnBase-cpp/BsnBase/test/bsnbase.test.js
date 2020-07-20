
var assert = require("assert");

Test("bsnbase", function (t) {
    var contract;
    t.Run("deploy", function (tt) {
        contract = xchain.Deploy({
            name: "bsnbase",
            code: "../src/bsnbase.wasm",
            lang: "c",
            init_args: {}
        })
    });

    t.Run("insert", function (tt) {
        resp = contract.Invoke("insert_data", {"base_key":"dev_001","base_value":"aaron"});
        assert.equal(resp.Body, "insert success");
    });

    t.Run("update", function (tt) {
        resp = contract.Invoke("update_data", {"base_key":"dev_001","base_value":"aaron.zhang"});
        assert.equal(resp.Body, "update success");
    });

    t.Run("select", function (tt) {
        resp = contract.Invoke("select_data", {"base_key":"dev_001"});
        assert.equal(resp.Body, "aaron.zhang");
    });

    t.Run("remove", function (tt) {
        resp = contract.Invoke("remove_data", {"base_key":"dev_001"});
        assert.equal(resp.Body, "remove success");
    });
})
