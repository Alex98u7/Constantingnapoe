import pytest

# class级别的fixture
@pytest.fixture(scope="class")
def class_fixture():
    print("\n--- class级别fixture：测试类开始执行 ---")
    yield
    print("\n--- class级别fixture：测试类执行结束 ---")

# function级别的fixture
@pytest.fixture(scope="function")
def function_fixture():
    print("\n    function级别fixture：测试用例开始执行")
    yield
    print("\n    function级别fixture：测试用例执行结束")

class TestClass1:
    def test_case1_1(self, class_fixture, function_fixture):
        print("        执行TestClass1中的test_case1_1")
        assert True

    def test_case1_2(self, class_fixture, function_fixture):
        print("        执行TestClass1中的test_case1_2")
        assert True

class TestClass2:
    def test_case2_1(self, class_fixture, function_fixture):
        print("        执行TestClass2中的test_case2_1")
        assert True

    def test_case2_2(self, class_fixture, function_fixture):
        print("        执行TestClass2中的test_case2_2")
        assert True